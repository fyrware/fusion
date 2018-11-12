# pragma once

# include <string>

namespace fusion::core {
    using std::string;

    class event {

        public:
            string event_type;
            int event_i;

            explicit event (const string& type, int i = 0) {
                event_type = type;
                event_i = i;
            };
    };
}