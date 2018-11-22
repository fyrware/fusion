# pragma once

# include <string>

namespace fusion {

    template <typename details_type = std::nullptr_t> class instruction {

        private:
            std::string instruction_name;
            details_type instruction_details;

        public:
            explicit instruction (const std::string& name, details_type details = nullptr) {
                instruction_name = name;
                instruction_details = details;
            }

            std::string& name () {
                return instruction_name;
            }

            details_type& details () {
                return instruction_details;
            }
    };
}