/*
	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++ CoRoutines.

	Copyright 2021, 2022 Chris M. (RealTimeChris)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/
/// ThreadPool.hpp - Header for the "Thread-Pool" related stuff.
/// Dec 18, 2021
/// https://discordcoreapi.com
/// \file ThreadPool.hpp

#pragma once

#ifndef THREAD_POOL
	#define THREAD_POOL

	#include <discordcoreapi/FoundationEntities.hpp>
	#include <discordcoreapi/Https.hpp>
	#include <coroutine>

namespace DiscordCoreAPI {
	/**
	 * \addtogroup utilities
	 * @{
	 */

	template<typename... ArgTypes> using TimeElapsedHandler = std::function<void(ArgTypes...)>;

	using TimeElapsedHandlerNoArgs = std::function<void(void)>;

	constexpr float percentage{ 10.0f / 100.0f };

	class DiscordCoreAPI_Dll ThreadPool {
	  public:
		ThreadPool& operator=(const ThreadPool&) = delete;

		ThreadPool(const ThreadPool&) = delete;

		ThreadPool() noexcept = default;

		static std::string storeThread(TimeElapsedHandlerNoArgs timeElapsedHandler, int64_t timeInterval);

		static void executeFunctionAfterTimePeriod(TimeElapsedHandlerNoArgs timeElapsedHandler, int64_t timeDelay, bool blockForCompletion) {
			std::jthread thread = std::jthread([=](std::stop_token stopToken) {
				StopWatch stopWatch{ std::chrono::milliseconds{ timeDelay } };
				stopWatch.resetTimer();
				std::this_thread::sleep_for(std::chrono::milliseconds{ static_cast<int64_t>(std::ceil(static_cast<float>(timeDelay) * percentage)) });
				while (!stopWatch.hasTimePassed() && !stopToken.stop_requested()) {
					std::this_thread::sleep_for(1ms);
				}
				if (stopToken.stop_requested()) {
					return;
				}
				timeElapsedHandler();
				if (stopToken.stop_requested()) {
					return;
				}
			});
			if (blockForCompletion) {
				if (thread.joinable()) {
					thread.join();
				}
			} else {
				if (thread.joinable()) {
					thread.detach();
				}
			}
		}

		template<typename... ArgTypes>
		static void executeFunctionAfterTimePeriod(TimeElapsedHandler<ArgTypes...> timeElapsedHandler, int64_t timeDelay, bool blockForCompletion, ArgTypes... args) {
			std::jthread thread = std::jthread([=](std::stop_token stopToken) {
				StopWatch stopWatch{ std::chrono::milliseconds{ timeDelay } };
				stopWatch.resetTimer();
				std::this_thread::sleep_for(std::chrono::milliseconds{ static_cast<int64_t>(std::ceil(static_cast<float>(timeDelay) * percentage)) });
				while (!stopWatch.hasTimePassed() && !stopToken.stop_requested()) {
					std::this_thread::sleep_for(1ms);
				}
				if (stopToken.stop_requested()) {
					return;
				}
				timeElapsedHandler(args...);
				if (stopToken.stop_requested()) {
					return;
				}
			});
			if (blockForCompletion) {
				if (thread.joinable()) {
					thread.join();
				}
			} else {
				if (thread.joinable()) {
					thread.detach();
				}
			}
		}

		void stopThread(const std::string& key);

		~ThreadPool() noexcept = default;

	  protected:
		static std::unordered_map<std::string, std::jthread> threads;
	};
}

namespace DiscordCoreInternal {

	struct DiscordCoreAPI_Dll WorkerThread {
		WorkerThread& operator=(WorkerThread&& other) noexcept;

		WorkerThread(WorkerThread&&) noexcept;

		WorkerThread() noexcept = default;

		~WorkerThread() noexcept = default;

		std::atomic_bool areWeCurrentlyWorking{ false };
		std::jthread thread{};
	};

	class DiscordCoreAPI_Dll CoRoutineThreadPool {
	  public:
		friend class DiscordCoreAPI::DiscordCoreClient;

		CoRoutineThreadPool();

		void submitTask(std::coroutine_handle<> coro) noexcept;

	  protected:
		std::deque<std::coroutine_handle<>> coroutineHandles{};
		std::unordered_map<int64_t, WorkerThread> workerThreads{};
		std::atomic_int64_t coroHandleCount{ 0 };
		std::atomic_int64_t currentCount{ 0 };
		std::atomic_int64_t currentIndex{ 0 };
		std::atomic_uint32_t threadCount{};
		std::mutex mutex{};

		void threadFunction(std::stop_token stopToken, int64_t index);
	};
	/**@}*/
}// namespace DiscordCoreAPI
#endif