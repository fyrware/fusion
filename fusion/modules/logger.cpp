# pragma once

# include <map>
# include <string>
# include <utility>

# include "fusion/core/module.cpp"

using namespace std;
using namespace fusion::core;

namespace fusion::modules {

    class logger : public module {

        public: string pattern;

        public: logger (string pattern) {
            this->pattern = move(pattern);
        }

        public: void connect (map<string, module>& modules) override {

        }

        public: void error (string message) {

        }

        public: void info (string message) {

        }

        public: void warn (string message) {

        }
    };
}