# pragma once

# include <functional>
# include <map>
# include <queue>
# include <thread>
# include <utility>

# include "fusion/core/module.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::modules {

    class thread_pool : public module {

        private: int size;
        private: map<thread::id, thread> pool;
        private: queue<function<void()>> actions;

        public: explicit thread_pool (int size = 2) {
            this->size = size;
        }

        public: void resize (int size) {
            if (this->size > size) {
                // remove X threads until right size
            }

            this->size = size;
        }

        public: void run (function<void()> callback) {
            actions.push(move(callback));

            if (pool.size() < size) {
                thread process = thread([ & ] () -> void {
                    while (pool.find(this_thread::get_id()) != pool.end()) {
                        if (actions.size() > 0) {
                            actions.front()();
                            actions.pop();
                        }
                    }
                });

                pool.emplace(process.get_id(), move(process));
            }
        }
    };
}