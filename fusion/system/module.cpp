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

        public: module () = default;

        public: virtual void connect (map<string, module>& registry) {

        }
    };
}
