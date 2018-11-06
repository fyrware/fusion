# pragma once

# include <any>
# include <exception>
# include <functional>
# include <utility>
# include <vector>

# include "fusion/core/executor.cpp"

namespace fusion::core {
    using std::any;
    using std::exception;
    using std::function;
    using std::vector;

    template <typename observation_type> class observable {

        private:
            vector<function<void()>> observable_actions;
            vector<function<void(exception)>> observable_catches;
            vector<observation_type> observable_observations;

            executor observable_observation_executor;
            executor observable_subscription_executor;

        public:
            observable () = default;

            observable (function<void(observable&)> observer) {
                observer(*this);
            }

            template <typename cast_type> observable<cast_type>& cast () {

            }

            observable<observation_type>& observe_concurrently (executor observation_executor) {
                observable_observation_executor = observation_executor;

                return *this;
            }

            observable<observation_type>& subscribe_concurrently (executor subscription_executor) {
                observable_subscription_executor = subscription_executor;

                return *this;
            }

            observable<observation_type>& for_each (function<void(observation_type)> callback) {
                observable_actions.emplace_back([ this, callback ] () {
                    for (observation_type observation : observable_observations) {
                        callback(observation);
                    }
                });

                return *this;
            }

            void pipe (observation_type observation) {
                observable_observations.emplace_back(observation);

                for (function<void()>& action : observable_actions) {
                    action();
                }

                observable_observations.clear();
            }

            observable<observation_type>& catch_exception (function<void(exception)> callback) {
                observable_catches.emplace_back(callback);

                return *this;
            }

            void throw_exception (exception thrown) {
                for (function<void(exception)>& caught : observable_catches) {
                    caught(thrown);
                }
            }
    };
}