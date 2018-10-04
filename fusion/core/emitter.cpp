# pragma once

# include <any>
# include <exception>
# include <functional>
# include <string>
# include <utility>
# include <vector>

# include "fusion/core/observable.cpp"

using namespace std;

namespace fusion::core {

    template <typename emission_type> class emitter {

        private: map<string, vector<observable<emission_type>*>> watchers;

        public: emitter () = default;

        public: observable<emission_type>* observe (string type) {
            auto* watcher = new observable<emission_type>();

            if (watchers.find(type) == watchers.end()) {
                watchers.emplace(type, vector<observable<emission_type>*>());
            }

            watchers.at(type).emplace_back(watcher);

            return watcher;
        }

        public: void emit (string type, emission_type emission) {
            if (watchers.find(type) != watchers.end()) {
                for (observable<emission_type>* watcher : watchers.at(type)) {
                    watcher->pipe(emission);
                }
            }
        }
    };
}