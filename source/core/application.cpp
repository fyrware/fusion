# include <array>
# include <fusion/core/event>
# include <fusion/core/plugin>

using namespace fusion::core;

namespace fusion::core {

    class application : public event::emitter {

        application (array<plugin> plugins) {

        }

        refresh (bool hard = false) {

        }

        start () {
            emit("start");
        }
    }
}
