# pragma once

# include <iostream>
# include <map>
# include <string>
# include <utility>
# include <vector>

# include "fusion/observable.cpp"

namespace fusion {

    const std::string EMITTER_OBSERVE_ALL;

    template <typename emission_type> class emitter {

        private:
            std::map<std::string, std::vector<observable<emission_type>*>> emitter_observers;

        public:
            explicit emitter () {
                emitter_observers.emplace(EMITTER_OBSERVE_ALL, std::vector<observable<emission_type>*>());
            };

            ~ emitter () {
                for (std::pair p : emitter_observers) {
                    std::vector<observable<emission_type>*>& observables = p.second;

                    for (observable<emission_type>* o : observables) {
                        delete o;
                        o = nullptr;
                    }
                }
            }

            void emit (const std::string& name, emission_type emission) {

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

            observable<emission_type>& observe (const std::string& name = EMITTER_OBSERVE_ALL) {
                observable<emission_type>* observer = new observable<emission_type>();

                if (emitter_observers.find(name) == emitter_observers.end()) {
                    emitter_observers.emplace(name, std::vector<observable<emission_type>*>());
                }

                emitter_observers.at(name).emplace_back(observer);

                return *observer;
            }
    };
}