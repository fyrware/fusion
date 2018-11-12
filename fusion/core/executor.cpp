# pragma once

# include <functional>
# include <queue>
# include <mutex>
# include <shared_mutex>
# include <string>
# include <thread>
# include <vector>

# include "fusion/core/pool.cpp"

namespace fusion::core {
    using std::function;
    using std::queue;
    using std::shared_mutex;
    using std::string;
    using std::thread;
    using std::unique_lock;
    using std::vector;

    class executor {

        private:
            queue<function<void()>> executor_actions;
            shared_mutex executor_mutex;
            int executor_thread_count;
            pool<thread> executor_thread_pool;

        public:
            explicit executor (int thread_count = 0) : executor_thread_pool(thread_count, [ & ] () -> thread {
                return thread([ & ] () {
                    function<void()> action = nullptr;

                    while (true) {
                        unique_lock<shared_mutex> guard(executor_mutex);

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

            void run (const function<void()>& action) {
                if (executor_thread_count == 0) {
                    action();
                }
                else {
                    executor_actions.push(action);
                }
            }
    };
}