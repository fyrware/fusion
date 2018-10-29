# pragma once

# include <any>
# include <exception>
# include <functional>
# include <utility>
# include <vector>

namespace fusion::core {
    using std::any;
    using std::exception;
    using std::function;
    using std::vector;

    template <typename observation_type> class observable {

        private: vector<function<void()>> actions;
        private: vector<function<void(exception)>> catches;
        private: vector<observation_type> observations;

        public: explicit observable (int size = 0) { }

        public: observable (function<void(observable*)> observer) {
            observer(this);
        }

        public: template <typename cast_type> observable<cast_type>& cast () {

        }

        public: observable<observation_type>& for_each (function<void(observation_type)> callback) {
            actions.emplace_back([ this, callback ] () {
                for (observation_type observation : observations) {
                    callback(observation);
                }
            });

            return *this;
        }

        public: observable<observation_type>& catch_exception (function<void(exception)> callback) {
            catches.emplace_back(callback);

            return *this;
        }

        public: void throw_exception (exception thrown) {
            for (auto& caught : catches) {
                caught(thrown);
            }
        }

        public: void pipe (observation_type observation) {
            observations.emplace_back(observation);

            for (auto& action : actions) {
                action();
            }

            observations.clear();
        }
    };
}