# pragma once

# include <functional>
# include <queue>
# include <mutex>
# include <shared_mutex>
# include <string>
# include <thread>
# include <vector>

# include "fusion/pool.cpp"

namespace fusion {

    class executor {

        private:
            std::queue<std::function<void()>> executor_actions;
            std::shared_mutex executor_mutex;
            int executor_thread_count;
            pool<std::thread> executor_thread_pool;

        public:
            explicit executor (const int thread_count = 0) : executor_thread_pool(thread_count, [ & ] () -> std::thread {
                return std::thread([ & ] () {
                    std::function<void()> action = nullptr;

                    while (true) {
                        std::unique_lock<std::shared_mutex> guard(executor_mutex);

                        if (!executor_actions.empty()) {
                            action = executor_actions.front();
                            executor_actions.pop();
                        }

                        guard.unlock();

                        if (action != nullptr) {
                            action();
                            action = nullptr;
                        }
                    }
                });
            }) {
                executor_thread_count = thread_count;
            }

            ~ executor () {
                for (std::size_t i = 0; i < executor_thread_pool.size(); ++i) {
                    executor_thread_pool.contents().at(i).detach();
                }
            }

            std::vector<std::thread>& threads () {
                return executor_thread_pool.contents();
            }

            void run (const std::function<void()>& action) {
                if (executor_thread_count == 0) {
                    action();
                }
                else {
                    executor_actions.push(action);
                }
            }
    };
}