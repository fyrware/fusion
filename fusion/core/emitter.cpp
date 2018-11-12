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

        private: map<string, vector<observable<emission_type>*>> observers;

        public: explicit emitter () = default;

        public: observable<emission_type>& observe (string type) {
            auto* observer = new observable<emission_type>();

            if (observers.find(type) == observers.end()) {
                observers.emplace(type, vector<observable<emission_type>*>());
            }

            observers.at(type).emplace_back(observer);

            return *observer; // TODO cleanup mem
        }

        public: void emit (string type, emission_type emission) {
            if (observers.find(type) != observers.end()) {
                for (observable<emission_type>* observer : observers.at(type)) {
                    observer->pipe(emission);
                }
            }
        }
    };
}