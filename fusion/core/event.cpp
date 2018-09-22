# include <algorithm>
# include <any>
# include <functional>
# include <map>
# include <string>
# include <vector>

using namespace std;

namespace fusion::core {

    class event {

        public: template <class observable_type> class observer {

            private: vector<function<void(observable_type)>> actions;
            private: vector<observable_type> queue;

            public: observer () = default;

            public: observer<observable_type>& debounce (function<void(observable_type, long)> callback) {
                actions.emplace_back([ & ] (observable_type observable) -> void {
                    for (long i = 0, count = queue.size(); i < count; ++i) {

                    }
                });

                return this;
            }

            public: observer<observable_type>& filter (function<bool(observable_type, long)> callback) {
                actions.emplace_back([ & ] (observable_type observable) -> void {
                    for (long i = 0, count = queue.size(); i < count; ++i) {

                    }
                });

                return this;
            }

            public: observer<observable_type>* for_each (function<void(observable_type, long)> callback) {
                actions.emplace_back([ & ] (observable_type observable) -> void {
                    for (long i = 0, count = queue.size(); i < count; ++i) {
                        callback(observable, i);
                    }
                });

                return this;
            }

            public: template <typename return_type> observer<return_type>& map (function<return_type(observable_type, long)> callback) {
                actions.emplace_back([ & ] (observable_type observable) -> void {
                    for (long i = 0, count = queue.size(); i < count; ++i) {

                    }
                });

                return this;
            }

            public: void pipe (observable_type observable) {
                queue.emplace_back(observable);

                for (auto& action : actions) {
                    action(observable);
                }

                queue.erase(remove(queue.begin(), queue.end(), observable));

                actions.clear();
            }
        };

        public: class emitter {

            private: map<string, vector<observer<event*>*>> subscriptions;

            public: emitter () = default;

            public: void emit (string name, map<string, any> data = { }) {
                event* observable = new event(this, name, move(data));

                if (subscriptions.find(name) != subscriptions.end()) {
                    for (auto subscriber : subscriptions.find(name)->second) {
                        subscriber->pipe(observable);
                    }
                }

                delete observable;
            }

            public: observer<event*>* subscribe (string name) {
                observer<event*>* subscriber = new observer<event*>();

                if (subscriptions.find(name) != subscriptions.end()) {
                    subscriptions.find(name)->second.emplace_back(subscriber);
                }
                else {
                    subscriptions.emplace(name, vector({ subscriber }));
                }

                return subscriber;
            }

            public: void unsubscribe (observer<event*>* subscriber) {
                for (auto& entry : subscriptions) {
                    if (find(entry.second.begin(), entry.second.end(), subscriber) != entry.second.end()) {
                        entry.second.erase(remove(entry.second.begin(), entry.second.end(), subscriber));
                    }
                }

                delete subscriber;
            }
        };

        public: emitter* target;
        public: string name;
        public: map<string, any> data;

        public: event (emitter* target, string name, map<string, any> data) {
            this->target = target;
            this->name = move(name);
            this->data = move(data);
        }

        public: template <typename value_type> value_type datum (string key) {
            return any_cast<value_type>(data.find(key)->second);
        }
    };
}