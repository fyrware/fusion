# pragma once

# include <functional>
# include <utility>

# include "fusion/core/broker.cpp"
# include "fusion/core/emitter.cpp"
# include "fusion/entities/event.cpp"
# include "fusion/entities/message.cpp"

namespace fusion::system {
    using std::function;
    using std::move;
    using fusion::core::broker;
    using fusion::core::emitter;
    using fusion::entities::event;
    using fusion::entities::message;

    class plugin {

        private:
            bool plugin_applied;
            function<void(broker<message>&)> plugin_patcher;

        public:
            explicit plugin (function<void(broker<message>&)> patcher) {
                plugin_applied = false;
                plugin_patcher = move(patcher);
            }

            void patch (broker<message>& app) {
                plugin_patcher(app);
                plugin_applied = true;
            }

            bool applied () {
                return plugin_applied;
            }
    };
}
