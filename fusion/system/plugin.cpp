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

        private: function<void(emitter<event>&)> patcher;

        public: bool applied = false;

        public: plugin (function<void(emitter<event>&)> patcher) {
            this->patcher = move(patcher);
        }

        public: void patch (emitter<event>& application) {
            patcher(application);
            applied = true;
        }
    };
}
