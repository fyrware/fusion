# include <iostream>

# include "fusion/program.cpp"

namespace example {

    void run () {
        fusion::program example;

        example.subscribe("program").observe("start").for_each([] (fusion::instruction x) {
            std::cout << x.name() << std::endl;
        });

        example.start();
        while (example.running());
    }
}

int main () {
    example::run();
}