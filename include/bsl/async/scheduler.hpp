#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <cstdint>
#include <functional>
#include <condition_variable>

class AsyncScheduler {
private:
	using Callback = std::function<void()>;

	using Clock     = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;
	using Duration  = std::chrono::milliseconds;
private:
	struct Timer {
		TimePoint     Time;
		std::uint64_t Order;
		Callback      Proc;

		bool operator<(const Timer& other) const {
			if (Time != other.Time)
				return Time > other.Time;
			return Order > other.Order;
		}
	};
public:
	std::priority_queue<Timer> m_Timers;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	std::thread m_Thread;
	std::uint64_t m_NextOrder = 0;
	bool m_Stop = false;
	bool m_Started = false;
public:

	AsyncScheduler() = default;

	~AsyncScheduler();

	AsyncScheduler(const AsyncScheduler&) = delete;

	AsyncScheduler& operator=(const AsyncScheduler&) = delete;

	void SetTimeout(Duration delay, Callback callback);

private:
	void Run();

};
