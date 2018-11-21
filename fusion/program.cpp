# pragma once

# include <functional>
# include <map>
# include <vector>
# include <utility>

# include "fusion/broker.cpp"
# include "fusion/instruction.cpp"

namespace fusion {

    class program : public broker<instruction> {

        private:
            bool program_running = false;

        public:
            explicit program (const std::vector<std::function<void(program&)>>& components = { }) {
                for (const std::function<void(program&)>& component : components) {
                    component(*this);
                }
            }

            bool running () {
                return program_running;
            }

            void start () {
                program_running = true;
                publish("program", "start", instruction("program::start"));
            }

            void exit () {
                program_running = false;
                publish("program", "exit", instruction("program::exit"));
            }
    };
}