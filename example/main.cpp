# include <iostream>
# include <string>
# include <typeinfo>

# include "fusion/core/event.cpp"
# include "fusion/system/application.cpp"

namespace example {
    using std::cout;
    using std::endl;
    using fusion::core::event;
    using fusion::system::application;

    void run () {
        application app;

        app.observe("start").for_each([] (event e) {
            cout << "application has started" << endl;
        });

        app.start();

        while (app.is_running());
    }
}

int main () {
    example::run();
}