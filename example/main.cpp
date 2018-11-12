# include <iostream>
# include <thread>

# include "fusion/core/event.cpp"
# include "fusion/core/executor.cpp"
# include "fusion/system/application.cpp"

namespace example {
    using std::cout;
    using std::endl;
    using fusion::core::event;
    using fusion::core::executor;
    using fusion::system::application;

    void run () {
        application app;
        executor exe(1);

        cout << "main thread: " << std::this_thread::get_id() << endl;

        app.observe("start").use_executor(exe).for_each([] (event e) {
            cout << "application has started: " << std::this_thread::get_id() << endl;
        });

        app.start();

        while (app.running());
    }
}

int main () {
    example::run();
}