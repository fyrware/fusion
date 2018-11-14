# pragma once

# include <algorithm>
# include <any>
# include <map>
# include <string>
# include <vector>
# include <utility>

# include "fusion/core/emitter.cpp"
# include "fusion/core/observable.cpp"

namespace fusion::core {
    using std::any;
    using std::find;
    using std::map;
    using std::pair;
    using std::random_shuffle;
    using std::string;
    using std::vector;

    const string BROKER_NO_TEAM;

    template <typename brokerage_type> class broker {

        private:
            map<string, vector<emitter<brokerage_type>*>> broker_subscribers;
            map<string, vector<emitter<brokerage_type>*>> broker_teams;

        public:
            broker () = default;

            emitter<brokerage_type>& subscribe (const string& topic, const string& team = BROKER_NO_TEAM) {
                if (broker_subscribers.find(topic) == broker_subscribers.end()) {
                    broker_subscribers.emplace(topic, vector<emitter<brokerage_type>*>());
                }

                auto* subscriber = new emitter<brokerage_type>;

                broker_subscribers.at(topic).emplace_back(subscriber);

                if (team != BROKER_NO_TEAM) {
                    if (broker_teams.find(team) == broker_teams.end()) {
                        broker_teams.emplace(team, vector<emitter<brokerage_type>*>());
                    }

                    broker_teams.at(team).emplace_back(subscriber);
                }

                return *subscriber;
            }

            void publish (const string& topic, const string& description, brokerage_type payload = brokerage_type()) {
                if (broker_subscribers.find(topic) != broker_subscribers.end()) {

                    for (emitter<brokerage_type>* subscriber : broker_subscribers.at(topic)) {

                        if (broker_teams.size() == 0) {
                            subscriber->emit(description, payload);
                        }
                        else for (pair p : broker_teams) {
                            vector<emitter<brokerage_type>*> team = p.second;

                            if (find(team.begin(), team.end(), subscriber) != team.end()) {
                                random_shuffle(team.begin(), team.end());
                                team.at(0)->emit(description, payload);
                            }
                            else {
                                subscriber->emit(description, payload);
                            }
                        }
                    }
                }
            }

            void publish (const string& topic, brokerage_type payload) {
                publish(topic, EMITTER_OBSERVE_ALL, payload);
            }
    };
}