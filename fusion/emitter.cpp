# pragma once

# include <map>
# include <string>
# include <thread>
# include <utility>
# include <vector>

# include "fusion/observable.cpp"

namespace fusion {
    using std::map;
    using std::pair;
    using std::string;
    using std::thread;
    using std::vector;

    const string EMITTER_OBSERVE_ALL;

    template <typename emission_type> class emitter {

        private:
            map<string, vector<observable<emission_type>*>> emitter_observers;

        public:
            explicit emitter () {
                emitter_observers.emplace(EMITTER_OBSERVE_ALL, vector<observable<emission_type>*>());
            };

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

            observable<emission_type>& observe (const string& name = EMITTER_OBSERVE_ALL) {
                auto* observer = new observable<emission_type>();

                if (emitter_observers.find(name) == emitter_observers.end()) {
                    emitter_observers.emplace(name, vector<observable<emission_type>*>());
                }

                emitter_observers.at(name).emplace_back(observer);

                return *observer;
            }

            void emit (const string& name, const emission_type emission) {
                if (emitter_observers.find(name) != emitter_observers.end()) {
                    for (observable<emission_type>* observer : emitter_observers.at(name)) {
                        observer->pipe(emission);
                    }
                }

                if (name != EMITTER_OBSERVE_ALL) {
                    for (observable<emission_type>* observer : emitter_observers.at(EMITTER_OBSERVE_ALL)) {
                        observer->pipe(emission);
                    }
                }
            }
    };
}