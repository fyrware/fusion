# include <any>
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
            
            vector<map<string, function>> actions;
            
            observable& debounce (function callback) {
				actions.push_back({ { "debounce", callback } });
                return this;
            }
            
            observable& filter (function callback) {
				actions.push_back({ { "filter", callback } });
                return this;
            }
            
            observable& for_each (function callback) {
				actions.push_back({ { "for_each", callback } });
                return this;
            }

			void pipe (event e) {
				for (int i = 0, int count = actions.size(); i < count; ++i) {
					map<string, any> action = actions.at(i);
					string name = action.
				}
			}
        }
        
        event (string name, map<string, any> details, target_type target) {
            
        }
    }
}
