# include <string>

# include <fusion/core/application.cpp>
# include <fusion/core/event.cpp>

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class module : public event::emitter {

        private:
            class application& host;

        public:
            virtual void connect (class application& host) {
                this->host = host;
            }
    };
}
