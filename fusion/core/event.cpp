# include <any>
# include <functional>
# include <map>
# include <string>
# include <vector>

using namespace std;

namespace fusion::core {

    class event {

        private:
            string name;
            emitter target;
            map<string, any> data;

        public:
            template <class observable_type> class observer {

                private:
                    vector<function<void(observable_type&)>> actions;
                    vector<event&> stream;

                public:
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

            class emitter {

                public:
                    emitter () {

                    }

                    void emit (string* name, map<string, int> data = { }) {

                    }

                    observer<event> subscribe (string* name) {

                    }
            };

            event (emitter target, string* name, map<string, string> data) {

            }

            template <typename value_type> value_type datum (const string& key) {

            }
    };
}
