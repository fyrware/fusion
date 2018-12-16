# pragma once

# include <exception>
# include <functional>
# include <memory>
# include <type_traits>
# include <vector>

# include "fusion/executor.cpp"

namespace fusion {

    executor DEFAULT_OBSERVABLE_EXECUTOR(0);

    template <typename observation_type> class observable {

        private:
            std::vector<function<void()>> observable_actions;
            executor* observable_executor;
            std::vector<observation_type> observable_observations;
            std::vector<void*> observable_casted_observables;

        public:
            observable () : observable_executor(&DEFAULT_OBSERVABLE_EXECUTOR) { };

            ~ observable () {
                for (void* casted_observable : observable_casted_observables) {
                    delete static_cast<observable<observation_type>*>(casted_observable);
                }
            }

            observable<observation_type>& use_executor (executor& executor_to_use) {
                observable_executor = &executor_to_use;

                return *this;
            }

            template <typename cast_type> observable<cast_type>& cast (bool dynamic = false) {
                observable<cast_type>* new_observable = new observable<cast_type>();

                observable_casted_observables.emplace_back(new_observable);
                observable_actions.emplace_back([ this, dynamic, new_observable ] () {
                    for (observation_type& observation : observable_observations) {
                        if (dynamic) {
                            new_observable->pipe(dynamic_cast<cast_type>(observation));
                        }
                        else {
                            new_observable->pipe(static_cast<cast_type>(observation));
                        }
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

                    if (std::is_pointer<observation_type>::value) {
                        for (observation_type observation : observable_observations) {
                            delete observation;
                        }
                    }

                    observable_observations.clear();
                });
            }
    };
}