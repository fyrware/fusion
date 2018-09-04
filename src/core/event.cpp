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
            
            observable () {
                
            }
            
            observable filter (function callback) {
                
            }
            
            observable for_each (function callback) {
                
            }
            
            observable map (function callback) {
                
            }
        }
        
        event (string name, map<string, any> details, target_type target) {
            
        }
    }
}
