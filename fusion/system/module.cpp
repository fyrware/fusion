# pragma once

# include <map>
# include <string>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"

namespace fusion::system {
    using std::map;
    using std::string;
    using fusion::core::emitter;
    using fusion::core::event;

    class module : public emitter<event> {

        private:
            string module_name;

        public:
            explicit module (string name) {
                module_name = name;
            };

            string name () {
                return module_name;
            }

            virtual void connect (const map<string, module>& registry) {

            }
    };
}
