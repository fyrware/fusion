# include <functional>
# include <map>
# include <string>
# include <vector>

using namespace std;

namespace fusion::core {

    class event {

        template <class observable_type> static class observer {

            vector<function<void(observable_type&)>> actions;
            vector<event&> stream;

            observer () {
                
            }

            observer& debounce (function<void(observable_type&, int)> callback) {
                actions.emplace_back([ & ] (observable_type& observable) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {

                    }
                });

                return *this;
            }

            observer& filter (function<bool(observable_type&, int)> callback) {
                actions.emplace_back([ & ] (observable_type& observable) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {
                        
                    }
                });

                return *this;
            }

            observer& for_each (function<void(observable_type&, int)> callback) {
                actions.emplace_back([ & ] (observable_type& observable) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {
                        callback(observable, i);
                    }
                });

                return *this;
            }

            template <typename return_type> observer& map (function<return_type(observable_type&, int)> callback) {
                actions.emplace_back([ & ] (observable_type& observable) -> void {
                    for (int i = 0, count = stream.size(); i < count; ++i) {

                    }
                });

                return *this;
            }

            void pipe (observable_type observable) {
                stream.emplace_back(&observable);

                for (int i = 0, count = actions.size(); i < count; ++i) {
                    actions.at(i)(observable);
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
