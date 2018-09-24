# pragma once

# include <map>
# include <vector>

# include "fusion/core/event.cpp"
# include "fusion/core/module.cpp"
# include "fusion/core/plugin.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class application : public event::emitter {

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
            emit("start");
        }
    };
}