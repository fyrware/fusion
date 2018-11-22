# pragma once

# include <variant>
# include <functional>
# include <map>
# include <vector>
# include <utility>

# include "fusion/broker.cpp"
# include "fusion/instruction.cpp"

namespace fusion {

    template <typename instruction_type> class program : public broker<instruction<instruction_type>> {

        private:
            bool program_running = false;
            int program_status = 0;

        public:
            explicit program (const std::vector<std::function<void(program&)>>& plugins = { }) {
                for (const std::function<void(program&)>& plugin : plugins) {
                    plugin(*this);
                }
            }

            bool running () {
                return program_running;
            }

            int status () {
                return program_status;
            }

            void start () {
                program_running = true;

                this->publish("program", "start", instruction("program::start", instruction_type()));
            }

            void exit (const int status = 0) {
                program_running = false;
                program_status = status;

                this->publish("program", "exit", instruction("program::exit", instruction_type()));
            }
    };
}