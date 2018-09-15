# include <string>
# include <fusion/core/event>

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class module : public event::emitter {

        &application host;

        virtual void connect (application& host) {
            this->host = host;
        }
    };
}
