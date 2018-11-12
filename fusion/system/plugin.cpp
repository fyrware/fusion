# pragma once

# include <functional>
# include <utility>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"

namespace fusion::system {
    using std::function;
    using std::move;
    using fusion::core::emitter;
    using fusion::core::event;

    class plugin {

        private:
            bool plugin_applied;
            function<void(emitter<event>&)> plugin_patcher;

        public:
            explicit plugin (function<void(emitter<event>&)> patcher) {
                plugin_applied = false;
                plugin_patcher = move(patcher);
            }

            void patch (emitter<event>& application) {
                plugin_patcher(application);
                plugin_applied = true;
            }

            bool applied () {
                return plugin_applied;
            }
    };
}
