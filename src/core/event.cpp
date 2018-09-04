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

            observable subscribe (string name) {

            }
        }
        
        static class observable {
            
            vector<function> actions;
            
            observable& debounce (function callback) {
                actions.push_back(callback);
                return this;
            }
            
            observable& filter (function callback) {
                actions.push_back(callback);
                return this;
            }
            
            observable& for_each (function callback) {
                actions.push_back(callback);
                return this;
            }
        }
        
        event (string name, map<string, any> details, target_type target) {
            
        }
    }
}
