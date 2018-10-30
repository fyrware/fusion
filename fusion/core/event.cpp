# pragma once

# include <string>

namespace fusion::core {
    using std::string;

    class event {

        public:
            string type;

            explicit event (const string& type) {
                this->type = type;
            };
    };
}