# pragma once

# include <string>

namespace fusion::core {
    using std::string;

    class event {

        public:
            string event_type;

            explicit event (const string& type) {
                event_type = type;
            };
    };
}