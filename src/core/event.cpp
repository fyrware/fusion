# include <any>
# include <array>
# include <function>
# include <map>
# include <string>
# include <vector>

using namespace std;

namespace fusion::core {

    template <class target_type> class event {

        static class emitter {

            emitter () {

            }

            void emit (string name, map<string, any> data) {

            }

            event::observable subscribe (string name) {

            }
        }

        static class observable {
            
            static enum class action {
                debounce,
                filter,
                for_each
            }

            vector<array<any>> actions;

            observable& debounce (function callback) {
                actions.push_back({ observable::action::debounce, callback });
                return this;
            }

            observable& filter (function callback) {
                actions.push_back({ observable::action::filter, callback });
                return this;
            }

            observable& for_each (function callback) {
                actions.push_back({ observable::action::for_each, callback });
                return this;
            }

            void pipe (event e) {
                for (int i = 0, int count = actions.size(); i < count; ++i) {
                    array<any> action = actions.at(i);
                    
                    switch (action[ 0 ]) {
                        case observable::action::debounce:
                            
                            break;
                            
                        case observable::action::filter:
                            
                            break;
                            
                        case observable::action::for_each:
                            
                            break;
                    }
                }
                
                actions.clear();
            }
        }

        event (string name, map<string, any> details, target_type target) {

        }
    }
}
