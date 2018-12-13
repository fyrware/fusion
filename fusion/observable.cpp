# pragma once

# include <exception>
# include <functional>
# include <memory>
# include <vector>

# include "fusion/executor.cpp"

namespace fusion {
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
            void* observable_casted;

        public:
            observable () : observable_executor(&default_observable_executor) { };

            ~ observable () {
                delete observable_casted;
            }

            observable<observation_type>& use_executor (executor& executor_to_use) {
                observable_executor = &executor_to_use;

                return *this;
            }

            template <typename cast_type> observable<cast_type>& cast () {
                observable<cast_type>* new_observable = new observable<cast_type>();

                observable_casted = new_observable;

                observable_actions.emplace_back([ this, new_observable ] () {
                    for (observation_type& observation : observable_observations) {
                        new_observable->pipe(static_cast<cast_type>(observation));
                    }
                });

                return *new_observable;
            }

            observable<observation_type>& for_each (const function<void(observation_type&)> callback) {
                observable_actions.emplace_back([ this, callback ] () {
                    for (observation_type& observation : observable_observations) {
                        callback(observation);
                    }
                });

                return *this;
            }

            void pipe (observation_type observation) {
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