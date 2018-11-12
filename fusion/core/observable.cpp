# pragma once

# include <exception>
# include <functional>
# include <vector>

# include "fusion/core/executor.cpp"

namespace fusion::core {
    using std::exception;
    using std::function;
    using std::vector;

    namespace {
        executor default_observable_executor(0);
    }

    template <typename observation_type> class observable {

        private:
            vector<function<void()>> observable_actions;
            executor* observable_executor;
            vector<observation_type> observable_observations;

        public:
            observable () : observable_executor(&default_observable_executor) { };

            observable<observation_type>& use_executor (executor& executor_to_use) {
                observable_executor = &executor_to_use;

                return *this;
            }

            observable<observation_type>& for_each (const function<void(observation_type)> callback) {
                observable_actions.emplace_back([ this, callback ] () {
                    for (const observation_type& observation : observable_observations) {
                        callback(observation);
                    }
                });

                return *this;
            }

            void pipe (const observation_type observation) {
                observable_executor->run([ this, observation ] () {
                    observable_observations.emplace_back(observation);

                    for (const function<void()>& action : observable_actions) {
                        action();
                    }

                    observable_observations.clear();
                });
            }
    };
}