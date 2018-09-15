# include <fusion/core/application>

using namespace fusion::core;

namespace fusion::core {

    class plugin {

        function<void(application&)> patcher;

        plugin (function<void(application&)> patcher) {
            this->patcher = patcher;
        }

        void patch (application& app) {
            patcher(app);
        }
    }
}
