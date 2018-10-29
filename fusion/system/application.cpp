# pragma once

# include <map>
# include <string>
# include <vector>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"
# include "fusion/system/module.cpp"
# include "fusion/system/plugin.cpp"

namespace fusion::system {
    using std::map;
    using std::string;
    using std::vector;
    using fusion::core::emitter;
    using fusion::core::event;
    using fusion::system::module;
    using fusion::system::plugin;

    class application : public emitter<event> {

        private: map<string, module> modules;
        private: vector<plugin> plugins;

        public: explicit application (map<string, module> modules = { }, const vector<plugin> plugins = { }) {
            this->modules = modules;
            this->plugins = plugins;

            for (auto& pair : modules) {
                pair.second.connect(modules);
            }

            refresh();
        }

        public: void refresh (bool hard = false) {
            for (auto& plugin : plugins) if (hard || plugin.applied) {
                plugin.patch(*this);
            }
        }

        public: void start () {
            emit("start", event("start", this));
        }

        public: void exit () {
            emit("exit", event("exit", this));
        }

        public: bool is_running () {
            return true; // TODO
        }
    };
}