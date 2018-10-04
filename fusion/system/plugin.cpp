# pragma once

# include <functional>
# include <utility>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::system {

    class plugin {

        private: function<void(emitter<event>*)> patcher;

        public: bool applied = false;

        public: plugin (function<void(emitter<event>*)> patcher) {
            this->patcher = move(patcher);
        }

        public: void patch (emitter<event>* application) {
            patcher(application);
            applied = true;
        }
    };
}
