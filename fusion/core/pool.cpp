# pragma once

# include <functional>
# include <map>
# include <mutex>
# include <queue>
# include <shared_mutex>
# include <string>
# include <thread>
# include <utility>

namespace fusion::core {
    using std::function;
    using std::map;
    using std::queue;
    using std::string;

    template <typename fill_type> class pool {

        private: int size;
        private: map<string, fill_type> contents;

        public: explicit pool (int size = 1) : size(0) {
            resize(size);
        }

        public: void resize (int size) {

        }

        public: void drain () {

        }
    };
}