# pragma once

# include <map>
# include <string>

using namespace std;

namespace fusion::core {

    class module {

        public: module () = default;

        public: virtual void connect (map<string, module>& modules) {

        }
    };
}
