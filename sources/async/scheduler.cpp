#include <bsl/async/scheduler.hpp>

AsyncScheduler::~AsyncScheduler() {
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Stop = true;
	}
	m_Condition.notify_all();
	if (m_Thread.joinable())
		m_Thread.join();
}

void AsyncScheduler::SetTimeout(Duration delay, Callback callback) {
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_Stop)
			return;
		if (!m_Started) {
			m_Thread  = std::thread([this]() { Run(); });
			m_Started = true;
		}
		m_Timers.push(Timer{Clock::now() + delay, m_NextOrder++, std::move(callback)});
	}
	m_Condition.notify_one();
}

void AsyncScheduler::Run() {
	for (;;) {
		Callback proc;
		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			m_Condition.wait(lock, [this]() { return m_Stop || !m_Timers.empty(); });
			if (m_Stop)
				return;

			TimePoint next = m_Timers.top().Time;
			if (Clock::now() < next) {
				m_Condition.wait_until(lock, next);
				continue;
			}

			proc = std::move(const_cast<Timer&>(m_Timers.top()).Proc);
			m_Timers.pop();
		}

		if (proc)
			proc();
	}
}
