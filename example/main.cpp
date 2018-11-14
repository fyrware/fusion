# include <iostream>

# include "fusion/entities/message.cpp"
# include "fusion/system/application.cpp"

namespace example {
    using fusion::entities::message;
    using fusion::system::application;

    void run () {
        application app;

        app.subscribe("application").observe().for_each([] (message m) {
            std::cout << m.content() << std::endl;
        });

        app.publish("application", "start", message("application has started"));

        app.start();
        while (app.running());
    }
}

int main () {
    example::run();
}