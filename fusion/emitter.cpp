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
            std::map<std::string, std::vector<observable<emission_type>*>> emitter_observables;

        public:
            explicit emitter () {
                emitter_observables.emplace(EMITTER_OBSERVE_ALL, std::vector<observable<emission_type>*>());
            };

            ~ emitter () {
                for (std::pair p : emitter_observables) {
                    std::vector<observable<emission_type>*>& observables = p.second;

                    for (observable<emission_type>* o : observables) {
                        delete o;
                        o = nullptr;
                    }
                }
            }

            void emit (const std::string& name, emission_type emission) {

                if (emitter_observables.find(name) != emitter_observables.end()) {
                    for (observable<emission_type>* o : emitter_observables.at(name)) {
                        o->pipe(emission);
                    }
                }

                if (name != EMITTER_OBSERVE_ALL) {
                    for (observable<emission_type>* o : emitter_observables.at(EMITTER_OBSERVE_ALL)) {
                        o->pipe(emission);
                    }
                }
            }

            observable<emission_type>& observe (const std::string& name = EMITTER_OBSERVE_ALL) {
                observable<emission_type>* o = new observable<emission_type>();

                if (emitter_observables.find(name) == emitter_observables.end()) {
                    emitter_observables.emplace(name, std::vector<observable<emission_type>*>());
                }

                emitter_observables.at(name).emplace_back(o);

                return *o;
            }
    };
}