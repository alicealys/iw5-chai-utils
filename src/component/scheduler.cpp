#include "stdinc.hpp"
#include <queue>

namespace scheduler
{
	namespace
	{
		std::queue<std::function<void()>> tasks;

		void execute()
		{
			while (!tasks.empty())
			{
				const auto task = tasks.front();

				const auto now = std::chrono::high_resolution_clock::now();

				task();
				tasks.pop();
			}
		}

		void server_frame()
		{
			reinterpret_cast<void (*)()>(0x50C1E0)();
			execute();
		}
	}

	void once(const std::function<void()>& callback)
	{
		tasks.push(callback);
	}

	void init()
	{
		utils::hook::call(0x50CEDC, server_frame);
	}
}