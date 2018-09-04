# include <string>

using namespace std;

namespace fusion::core {

    template <class type> class event {
        
        private:
            string name;
            type target;
        
        public:
            event (string name, type target) {
                
            }
        
            string get_name () {
                return name;
            }
        
            type get_target () {
                return target;
            }
    }
}
