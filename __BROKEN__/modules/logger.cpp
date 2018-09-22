# include <iostream>
# include <regex>
# include <string>
# include <fusion/core/module>

using namespace std;

namespace fusion::modules {

    class logger : public module {

        string pattern;

        logger (string x = "(<when>) [ <type> ] <message>") {
            pattern = x;
        }

        void info (string message) {

        }

        void warn (string message) {

        }

        void error (string message) {

        }
    }
}
