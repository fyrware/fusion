# pragma once

# include <map>
# include <string>
# include <thread>
# include <utility>
# include <vector>

# include "fusion/core/observable.cpp"

namespace fusion::core {
    using std::map;
    using std::pair;
    using std::string;
    using std::thread;
    using std::vector;

    template <typename emission_type> class emitter {

        private:
            map<string, vector<observable<emission_type>*>> emitter_observers;

        public:
            explicit emitter () = default;

            ~ emitter () {
                for (pair p : emitter_observers) {
                    vector<observable<emission_type>*> observers = p.second;

                    for (observable<emission_type>* o : observers) {
                        delete o;
                    }

                    observers.clear();
                }

                emitter_observers.clear();
            }

            observable<emission_type>& observe (const string& type) {
                auto* observer = new observable<emission_type>();

                if (emitter_observers.find(type) == emitter_observers.end()) {
                    emitter_observers.emplace(type, vector<observable<emission_type>*>());
                }

                emitter_observers.at(type).emplace_back(observer);

                return *observer; // TODO cleanup mem
            }

            void emit (const string& type, const emission_type emission) {
                if (emitter_observers.find(type) != emitter_observers.end()) {
                    for (observable<emission_type>* observer : emitter_observers.at(type)) {
                        observer->pipe(emission);
                    }
                }
            }
    };
}