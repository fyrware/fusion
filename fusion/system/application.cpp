# pragma once

# include <map>
# include <string>
# include <utility>
# include <vector>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"
# include "fusion/system/module.cpp"
# include "fusion/system/plugin.cpp"

namespace fusion::system {
    using std::map;
    using std::move;
    using std::pair;
    using std::string;
    using std::vector;
    using fusion::core::emitter;
    using fusion::core::event;
    using fusion::system::module;
    using fusion::system::plugin;

    class application : public emitter<event> {

        private:
            map<string, module> application_modules;
            vector<plugin> application_plugins;
            bool application_running;

        public:
            explicit application (const map<string, module>& modules = { }, const vector<plugin>& plugins = { }) {
                application_modules = modules;
                application_plugins = plugins;
                application_running = false;

                for (pair p : application_modules) {
                    p.second.connect(application_modules);
                }

                refresh();
            }

            bool running () {
                return application_running;
            }

            map<string, module> modules () {
                return application_modules;
            }

            void refresh (const bool hard = false) {
                for (plugin p : application_plugins) if (hard || !p.applied()) {
                    p.patch(*this);
                }
            }

            void start () {
                application_running = true;

                emit("start", event("start"));
            }

            void exit () {
                application_running = false;

                emit("exit", event("exit"));
            }
    };
}