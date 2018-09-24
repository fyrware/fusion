# pragma once

# include <functional>
# include <utility>

# include "fusion/core/event.cpp"

using namespace fusion::core;

namespace fusion::core {

    class plugin {

        private: function<void(event::emitter*)> patcher;

        public: bool applied = false;

        public: plugin (function<void(event::emitter*)> patcher) {
            this->patcher = move(patcher);
        }

        public: void patch (event::emitter* application) {
            patcher(application);
            applied = true;
        }
    };
}
