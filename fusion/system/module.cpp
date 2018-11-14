# pragma once

# include <map>
# include <string>

# include "fusion/core/broker.cpp"
# include "fusion/core/emitter.cpp"
# include "fusion/entities/event.cpp"
# include "fusion/entities/message.cpp"

namespace fusion::system {
    using std::map;
    using std::string;
    using fusion::core::broker;
    using fusion::core::emitter;
    using fusion::entities::event;
    using fusion::entities::message;

    class module {

        public:
            module () = default;

            virtual void connect (broker<message>& app) {

            }
    };
}
