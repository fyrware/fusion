# pragma once

# include <string>

# include "fusion/core/emitter.cpp"

namespace fusion::core {
    using std::string;
    using fusion::core::emitter;

    class event {

        public: emitter<event>* source;
        public: string type;

        public: event (const string& type, emitter<event>* source) {
            this->type = type;
            this->source = source;
        };
    };
}