# pragma once

# include <map>
# include <vector>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"

# include "fusion/system/module.cpp"
# include "fusion/system/plugin.cpp"

using namespace std;
using namespace fusion::core;
using namespace fusion::system;

namespace fusion::system {

    class application : public emitter<event> {

        private: map<string, module> modules;
        private: vector<plugin> plugins;

        public: explicit application (map<string, module> modules = { }, vector<plugin> plugins = { }) {
            this->modules = modules;
            this->plugins = plugins;

            for (auto& pair : modules) {
                pair.second.connect(modules);
            }

            refresh();
        }

        public: void refresh (bool hard = false) {
            for (auto& plugin : plugins) if (hard || plugin.applied) {
                plugin.patch(this);
            }
        }

        public: void start () {
            emit("start", event("start", this));
        }

        public: void exit () {
            emit("exit", event("exit", this));
        }

        public: void foo () {
            emit("foo", event("foo", this));
        }
    };
}