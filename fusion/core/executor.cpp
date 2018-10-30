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
            queue<function<void()>> actions;
            mutable shared_mutex executor_mutex;
            pool<thread> thread_pool;

        public:
            explicit executor (int concurrency) : thread_pool(concurrency, [ & ] () -> thread {
                return thread([ & ] () {
                    function<void()> action = nullptr;

                    while (true) {
                        unique_lock<shared_mutex> guard(executor_mutex);

                        if (!actions.empty()) {
                            action = actions.front();
                            actions.pop();
                        }

                        guard.unlock();

                        if (action != nullptr) {
                            action();
                            action = nullptr;
                        }
                    }
                });
            }) {
                // thanks, c++ for this *lovely* syntax...
            }

            void run (const function<void()>& action) {
                actions.push(action);
            }
    };
}