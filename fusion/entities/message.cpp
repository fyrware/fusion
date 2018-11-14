# pragma once

# include <any>
# include <map>
# include <string>

namespace fusion::entities {
    using std::any;
    using std::any_cast;
    using std::map;
    using std::string;

    class message {

        private:
            string message_content;

        public:
            message () = default;

            explicit message (const string& content) {
                message_content = content;
            }

            string content () {
                return message_content;
            }
    };
}