#pragma once

#include <map>
#include <deque>
#include <mutex>
#include <thread>
#include <string>
#include <cstdint>
#include <cstddef>
#include <functional>
#include <condition_variable>

struct AsyncWorkerTask {
	std::function<void()> Proc;
};

using AsyncTaskPriority = std::int32_t;
static constexpr AsyncTaskPriority AsyncDefaultPriority = 0;

class AsyncWorker {
	std::map<AsyncTaskPriority, std::deque<AsyncWorkerTask>> m_Tasks;
	std::size_t m_TaskCount = 0;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	bool m_Stop    = false;
	bool m_Started = false;
	std::thread m_Thread;
	std::string m_Name;
public:
	AsyncWorker() = default;

	explicit AsyncWorker(std::string name): 
        m_Name(std::move(name)) 
    {}

	~AsyncWorker();

	AsyncWorker(const AsyncWorker&) = delete;

	AsyncWorker& operator=(const AsyncWorker&) = delete;

	void AddTask(AsyncTaskPriority priority, AsyncWorkerTask task);

	void AddTask(AsyncWorkerTask task);

	void Async(AsyncTaskPriority priority, std::function<void()> proc);

	void Async(std::function<void()> proc);

private:
	void Run();
};
