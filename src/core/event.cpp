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

            vector<array<any>> actions;

            observable& debounce (function callback) {
                actions.push_back({ "debounce", callback });
                return this;
            }

            observable& filter (function callback) {
                actions.push_back({ "filter", callback });
                return this;
            }

            observable& for_each (function callback) {
                actions.push_back({ "for_each", callback });
                return this;
            }

            void pipe (event e) {
                for (int i = 0, int count = actions.size(); i < count; ++i) {
                    array<any> action = actions.at(i);
                    string name = action[ 0 ];
                    function callback = action[ 1 ];
                    
                    if (name.compare("debounce") == 0) {
                        
                    }
                    
                    if (name.compare("filter") == 0) {
                        
                    }
                    
                    if (name.compare("for_each") == 0) {
                        
                    }
                }
                
                actions.clear();
            }
        }

        event (string name, map<string, any> details, target_type target) {

        }
    }
}
