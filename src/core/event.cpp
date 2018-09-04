# include <map>
# include <string>

using namespace std;

namespace fusion::core {

    class event {
        
        public : static class emitter {
        
            public : emitter () {

            }

            public : emit (string name, map data) {

            }

            public : subscribe (string name) {

            }

            public : unsubscribe () {

            }
        }
        
        public : static class observable {
            
            public : observable () {
                
            }
            
            public : for_each () {
                
            }
        }
        
        public : event () {
            
        }
    }
}
