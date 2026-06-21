#include <bsl/async/worker.hpp>

AsyncWorker::~AsyncWorker() {
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Stop = true;
	}
	m_Condition.notify_all();
	if (m_Thread.joinable())
		m_Thread.join();
}

void AsyncWorker::AddTask(AsyncTaskPriority priority, AsyncWorkerTask task) {
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_Stop)
			return;
		if (!m_Started) {
			m_Thread  = std::thread([this]() { Run(); });
			m_Started = true;
		}
		m_Tasks[priority].push_back(std::move(task));
		++m_TaskCount;
	}
	m_Condition.notify_one();
}

void AsyncWorker::AddTask(AsyncWorkerTask task) {
	AddTask(AsyncDefaultPriority, std::move(task));
}

void AsyncWorker::Async(AsyncTaskPriority priority, std::function<void()> proc) {
	AddTask(priority, {std::move(proc)});
}

void AsyncWorker::Async(std::function<void()> proc) {
	Async(AsyncDefaultPriority, std::move(proc));
}

void AsyncWorker::Run() {
	for (;;) {
		AsyncWorkerTask task;
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]() { return m_Stop || m_TaskCount > 0; });

			if (m_Stop && m_TaskCount == 0)
				return;

			auto bucket = m_Tasks.begin();
			task = std::move(bucket->second.front());
			bucket->second.pop_front();
			--m_TaskCount;
			if (bucket->second.empty())
				m_Tasks.erase(bucket);
		}
		task.Proc();
	}
}
