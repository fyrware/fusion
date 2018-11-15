# include <iostream>

# include "fusion/program.cpp"

namespace example {

    void run () {
        fusion::program example;

        example.subscribe("program").observe("start").for_each([] (int x) {
            std::cout << x << std::endl;
        });

        example.start();
        while (example.running());
    }
}

int main () {
    example::run();
}