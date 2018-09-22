# include <functional>

# include <fusion/core/application.cpp>

using namespace fusion::core;

namespace fusion::core {

    class plugin {

        private:
            function<void(application&)> patcher;

        public:
            plugin (function<void(application&)> patcher) {
                this->patcher = patcher;
            }

            void patch (application& app) {
                patcher(app);
            }
    };
}
