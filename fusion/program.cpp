# pragma once

# include <functional>
# include <map>
# include <vector>
# include <utility>

# include "fusion/broker.cpp"

namespace fusion {

    namespace {
        using std::is_function;
        int foo = 5;
    }

    class program : public broker<int> {

        private:
            bool program_running = false;

        public:
            explicit program (const std::vector<std::function<void(program&)>>& plugins = { }) {
                for (const std::function<void(program&)>& plugin : plugins) {
                    plugin(*this);
                }
            }

            bool running () {
                return program_running;
            }

            void start () {
                program_running = true;
                publish("program", "start", 0);
            }

            void exit () {
                program_running = false;
            }
    };
}