# pragma once

# include <algorithm>
# include <functional>
# include <iostream>
# include <queue>
# include <mutex>
# include <string>
# include <thread>
# include <utility>
# include <vector>

# include "fusion/pool.cpp"

namespace fusion {

    class executor {

        private:
            std::queue<std::function<void()>> executor_actions;
            std::mutex executor_mutex;
            int executor_thread_count;
            bool executor_running;
            bool executor_terminated;
            pool<std::thread> executor_thread_pool;

            void execute_next_action () {
                std::function<void()> action = nullptr;

                executor_mutex.lock();

                if (!executor_actions.empty()) {
                    action = executor_actions.front();
                    executor_actions.pop();
                }

                executor_mutex.unlock();

                if (action != nullptr) {
                    action();
                    action = nullptr;
                }
            }

        public:
            explicit executor (const int thread_count = 0) : executor_thread_pool(thread_count, [ this ] () -> std::thread {
                return std::thread([ this ] () {
                    while (!executor_terminated) if (executor_running) {
                        execute_next_action();
                    }
                });
            }) {
                executor_running = true;
                executor_terminated = false;
                executor_thread_count = thread_count;
            }

            ~ executor () {
                terminate();
                flush();
            }

            void advance () {
                executor_running = true;
            }

            void flush () {
                interrupt();

                while (!executor_actions.empty()) {
                    execute_next_action();
                }

                advance();
            }

            void interrupt () {
                executor_running = false;
            }

            void run (std::function<void()> action) {
                if (executor_running && executor_thread_count == 0) {
                    action();
                }
                else {
                    executor_actions.push(action);
                }
            }

            void terminate () {
                executor_running = false;
                executor_terminated = true;

                for (std::size_t i = 0; i < executor_thread_count; ++i) {
                    if (executor_thread_pool.contents().at(i).joinable()) {
                        executor_thread_pool.contents().at(i).join();
                    }
                }
            }
    };
}