# pragma once

# include <map>
# include <string>
# include <utility>
# include <vector>

# include "fusion/core/broker.cpp"
# include "fusion/entities/message.cpp"
# include "fusion/system/module.cpp"
# include "fusion/system/plugin.cpp"

namespace fusion::system {
    using std::map;
    using std::move;
    using std::pair;
    using std::string;
    using std::vector;
    using fusion::core::broker;
    using fusion::entities::message;

    class application : public broker<message> {

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
                    p.second.connect(*this);
                }

                refresh();
            }

            bool running () {
                return application_running;
            }

            void refresh (const bool hard = false) {
                for (plugin p : application_plugins) if (hard || !p.applied()) {
                    p.patch(*this);
                }
            }

            void start () {
                application_running = true;
            }

            void exit () {
                application_running = false;
            }
    };
}