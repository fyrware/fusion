# pragma once

# include <string>

# include "fusion/core/emitter.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::core {

    class event {

        public: emitter<event>* source;
        public: string type;

        public: event (string type, emitter<event>* source) {
            this->type = type;
            this->source = source;
        };
    };
}