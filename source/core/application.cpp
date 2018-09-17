# include <map>
# include <vector>
# include <fusion/core/event>
# include <fusion/core/module>
# include <fusion/core/plugin>

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class application : public event::emitter {

        map<string, module*> modules;
        vector<plugin> plugins;

        application (map<string, module*> modules, vector<plugin*> plugins) {
            this->modules = modules;
            this->plugins = plugins;

            for (const auto& entry : modules) {
                entry.second.connect(&this);
            }

            refresh();
        }

        module* module (string name) {
            return modules.find(name)->second;
        }

        void refresh (bool hard = false) {
            for (plugin x : plugins) if (hard || !x.applied) {
                x.patch(&this);
            }
        }

        void start () {
            emit("start");
        }
    }
}
