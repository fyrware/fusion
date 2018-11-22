# include <iostream>

# include "fusion/program.cpp"

namespace example {

    int run () {
        fusion::program<int> example;

        example.subscribe("foo").observe("bar").for_each([ & ] (fusion::instruction<int> x) {
            example.exit(x.details());
        });

        example.subscribe("program").observe("start").for_each([ & ] (fusion::instruction<int> x) {
            example.publish("foo", "bar", fusion::instruction<int>("foo::bar", 0));
        });

        example.start();

        while (example.running());
        return example.status();
    }
}

int main () {
    return example::run();
}