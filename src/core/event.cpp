# include <functional>
# include <map>
# include <string>
# include <vector>

using namespace std;

namespace fusion::core {

    class event {

        static class observer {

            vector<function<void(event&)>> actions;
            vector<event&> stream;

            observer () {
                
            }

            observer& debounce (function<void(event&, int)> callback) {
                actions.emplace_back([ & ] (event& e) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {

                    }
                });

                return *this;
            }

            observer& filter (function<bool(event&, int)> callback) {
                actions.emplace_back([ & ] (event& e) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {
                        
                    }
                });

                return *this;
            }

            observer& for_each (function<void(event&, int)> callback) {
                actions.emplace_back([ & ] (event& e) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {
                        callback(e, i);
                    }
                });

                return *this;
            }

            template <typename return_type> observer& map (function<return_type(event&, int)> callback) {
                actions.emplace_back([ & ] (event& e) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {

                    }
                });

                return *this;
            }

            void pipe (event e) {
                stream.emplace_back(&e);

                for (int i = 0, count = actions.size(); i < count; ++i) {
                    actions.at(i)(e);
                }

                // TODO clean up memory

                actions.clear();
            }
        };

        static class emitter {

            emitter () {

            }

            void emit (string* name, map<string, int>* data) {

            }

            observer subscribe (string* name) {

            }
        };

        event (string* name, map<string, int>* data, emitter target) {

        }
    };
}
