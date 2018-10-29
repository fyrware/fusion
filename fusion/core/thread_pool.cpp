# pragma once

# include <functional>
# include <map>
# include <mutex>
# include <queue>
# include <shared_mutex>
# include <thread>
# include <utility>

namespace fusion::core {
    using std::function;
    using std::map;
    using std::queue;
    using std::shared_mutex;
    using std::thread;
    using std::unique_lock;

    namespace {
        namespace this_thread = std::this_thread;
    }

    class thread_pool {

        private: int size;
        private: mutable shared_mutex pool_mutex;
        private: map<thread::id, thread> workers;
        private: queue<function<void()>> actions;

        public: explicit thread_pool (int size = 1) {
            resize(size);
        }

        public: void resize (int size) {
            if (this->size > size) {
                // remove X threads until right size
            }
            else while (workers.size() < size) {
                thread worker([ & ] () -> void {
                    function<void()> action = nullptr;

                    while (workers.find(this_thread::get_id()) != workers.end()) {
                        {
                            auto lock = unique_lock<shared_mutex>(pool_mutex);

                            if (actions.size() > 0) {
                                action = actions.front();
                                actions.pop();
                            }

                            lock.unlock();
                        }
                        if (action != nullptr) {
                            action();
                            action = nullptr;
                        }
                    }
                });

                workers.emplace(worker.get_id(), move(worker));
            }

            this->size = size;
        }

        public: void run (function<void()> callback) {
            if (this->size == 0) {
                move(callback)();
            }
            else {
                actions.push(move(callback));
            }
        }
    };
}