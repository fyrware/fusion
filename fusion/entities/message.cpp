# pragma once

# include <any>
# include <map>
# include <string>

namespace fusion::entities {
    using std::any;
    using std::any_cast;
    using std::map;
    using std::string;

    const string MESSAGE_EMPTY;

    class message {

        private:
            string message_content;

        public:
            explicit message (const string& content = MESSAGE_EMPTY) {
                message_content = content;
            }

            string content () {
                return message_content;
            }
    };
}