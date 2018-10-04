# pragma once

# include <map>
# include <string>

# include "fusion/core/emitter.cpp"
# include "fusion/core/event.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::system {

class module : public emitter<event> {

        public: module () = default;

        public: virtual void connect (map<string, module>& registry) {

        }
    };
}
