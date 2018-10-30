# pragma once

# include <algorithm>
# include <functional>
# include <queue>
# include <string>
# include <vector>

namespace fusion::core {
    using std::function;
    using std::queue;
    using std::string;
    using std::vector;

    template <typename fill_type> class pool {

        private:
            int size;
            function<fill_type()> allocator;
            vector<fill_type> contents;

        public:
            pool (int size, function<fill_type()> allocator) {
                this->allocator = allocator;
                this->size = 0;

                resize(size);
            }

            void resize (int size) {
                if (this->size > size) {
                    // todo: remove n contents until right-sized
                }
                else while (contents.size() < size) {
                    contents.emplace_back(allocator());
                }

                this->size = size;
            }

            typename vector<fill_type>::iterator find (fill_type element) {
                return std::find(contents.begin(), contents.end(), element);
            }

            typename vector<fill_type>::iterator end () {
                return contents.end();
            }
    };
}

//namespace fusion::core {
//    using std::function;
//    using std::map;
//    using std::queue;
//    using std::thread;
//
//    namespace {
//        namespace this_thread = std::this_thread;
//    }
//
//    class thread_pool {
//
//        private: int size;
//        private: mutable shared_mutex pool_mutex;
//        private: map<thread::id, thread> workers;
//        private: queue<function<void()>> actions;
//
//        public: explicit thread_pool (int size = 1) {
//            resize(size);
//        }
//
//        public: void resize (int size) {
//            if (this->size > size) {
//                // remove X threads until right size
//            }
//            else while (workers.size() < size) {
//                thread worker([ & ] () -> void {
//                    function<void()> action = nullptr;
//
//                    while (workers.find(this_thread::get_id()) != workers.end()) {
//                        {
//                            auto lock = unique_lock<shared_mutex>(pool_mutex);
//
//                            if (actions.size() > 0) {
//                                action = actions.front();
//                                actions.pop();
//                            }
//
//                            lock.unlock();
//                        }
//                        if (action != nullptr) {
//                            action();
//                            action = nullptr;
//                        }
//                    }
//                });
//
//                workers.emplace(worker.get_id(), move(worker));
//            }
//
//            this->size = size;
//        }
//
//        public: void run (function<void()> callback) {
//            if (this->size == 0) {
//                move(callback)();
//            }
//            else {
//                actions.push(move(callback));
//            }
//        }
//    };
//}