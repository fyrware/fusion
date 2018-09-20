# include <map>
# include <vector>

# include <fusion/core/event.cpp>
# include <fusion/core/module.cpp>
# include <fusion/core/plugin.cpp>

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class application : public event::emitter {

        private:
            map<string, module*> modules;
            vector<plugin*> plugins;

        public:
            application (map<string, module*> modules, vector<plugin*> plugins = { }) {
                this->modules = modules;
                this->plugins = plugins;

                for (const auto& entry : modules) {
                    entry.second->connect(*this);
                }

                refresh();
            }

            module* module (string name) {
                return modules.find(name)->second;
            }

            void refresh (bool hard = false) {
                for (plugin* x : plugins) if (hard || !x.applied) {
                    x->patch(*this);
                }
            }

            void start () {
                emit("start");
            }
    };
}
