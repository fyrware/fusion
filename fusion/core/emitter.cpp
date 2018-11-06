# pragma once

# include <map>
# include <string>
# include <thread>
# include <vector>

# include "fusion/core/observable.cpp"

namespace fusion::core {
    using std::map;
    using std::string;
    using std::thread;
    using std::vector;

    template <typename emission_type> class emitter {

        private: map<string, vector<observable<emission_type>*>> subscribers;

        public: explicit emitter () = default;

        public: observable<emission_type>& observe (string type) {
            auto* subscriber = new observable<emission_type>();

            if (subscribers.find(type) == subscribers.end()) {
                subscribers.emplace(type, vector<observable<emission_type>*>());
            }

            subscribers.at(type).emplace_back(subscriber);

            return *subscriber; // TODO cleanup mem
        }

        public: void emit (string type, emission_type emission) {
            if (subscribers.find(type) != subscribers.end()) {
                for (observable<emission_type>* observer : subscribers.at(type)) {
                    observer->pipe(emission);
                }
            }
        }
    };
}