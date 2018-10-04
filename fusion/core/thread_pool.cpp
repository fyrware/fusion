# pragma once

# include <functional>
# include <map>
# include <mutex>
# include <queue>
# include <shared_mutex>
# include <thread>
# include <utility>

using namespace std;

namespace fusion::core {

    class thread_pool {

        private: int size;
        private: mutable shared_mutex pool_mutex;
        private: map<thread::id, thread> workers;
        private: queue<function<void()>> actions;

        public: explicit thread_pool (int size = 2) {
            resize(size);
        }

        public: void resize (int size) {
            if (this->size > size) {
                // remove X threads until right size
            }
            else {
                while (workers.size() < size) {
                    thread process = thread([ & ] () -> void {
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

                    workers.emplace(process.get_id(), move(process));
                }
            }

            this->size = size;
        }

        public: void run (function<void()> callback) {
            actions.push(move(callback));
        }
    };
}