# pragma once

# include <any>
# include <map>
# include <string>

namespace fusion::entities {
    using std::any;
    using std::any_cast;
    using std::map;
    using std::string;

    class event {

        private:
            map<string, any> event_details;
            string event_name;

        public:
            explicit event (const string& name, const map<string, any>& details = { }) {
                event_details = details;
                event_name = name;
            };

            template <typename detail_type> detail_type detail (const string& key) {
                if (event_details.find(key) == event_details.end()) {
                    return nullptr;
                }
                else {
                    return any_cast<detail_type>(event_details.at(key));
                }
            }
    };
}