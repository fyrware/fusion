# pragma once

# include <exception>
# include <functional>
# include <iostream>
# include <memory>
# include <type_traits>
# include <utility>
# include <vector>

# include "fusion/executor.cpp"

namespace fusion {

    executor DEFAULT_OBSERVABLE_EXECUTOR;

    template <typename observation_type> class observable {

        private:
            std::vector<std::function<void()>> observable_actions;
            std::vector<void*> observable_casted_observables;
            executor* observable_executor;
            std::vector<observation_type> observable_observations;

        public:
            observable () : observable_executor(&DEFAULT_OBSERVABLE_EXECUTOR) { };

            ~ observable () {
                observable_executor->flush();

                for (void* casted_observable : observable_casted_observables) {
                    delete static_cast<observable<observation_type>*>(casted_observable);
                    casted_observable = nullptr;
                }
            }

            template <typename cast_type> observable<cast_type>& cast () {
                observable<cast_type>* new_observable = new observable<cast_type>();

                observable_casted_observables.emplace_back(new_observable);
                observable_actions.emplace_back([ this, new_observable ] () {
                    for (observation_type& observation : observable_observations) {
                        new_observable->pipe(static_cast<cast_type>(observation));
                    }
                });

                return new_observable->use_executor(*observable_executor);
            }

            observable<observation_type>& for_each (std::function<void(observation_type&)> callback) {
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

                    for (const std::function<void()>& action : observable_actions) {
                        action();
                    }

                    if (std::is_pointer<observation_type>::value && observable_casted_observables.empty()) { // TODO improve this? without checking if casted observables is empty,
                        for (observation_type observation : observable_observations) {                       // TODO we get invalid pointer, or double delete, or whatever it's called.
                            delete observation;                                                              // TODO solution breaks if more than one casted observable? maybe.
                            observation = nullptr;                                                           // TODO should have listened, and used smart pointers. ego. oof.
                        }
                    }

                    observable_observations.clear();
                });
            }

            observable<observation_type>& use_executor (executor& executor_to_use) {
                observable_executor = &executor_to_use;

                return *this;
            }
    };
}