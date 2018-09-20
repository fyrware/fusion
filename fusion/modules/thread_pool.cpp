# include <functional>
# include <thread>
# include <vector>
# include <fusion/core/module>

using namespace std;
using namespace fusion::core;

namespace fusion::modules {

    class thread_pool : public module {

        vector<thread> pool;

        thread_pool (int size = 8) {
            
        }
    };
}
