# pragma once

# include <string>

namespace fusion {

    class instruction {

        private:
            std::string instruction_name;

        public:
            explicit instruction (const std::string& name) {
                instruction_name = name;
            }

            std::string name () {
                return instruction_name;
            }
    };
}