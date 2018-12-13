# include <iostream>
# include <map>
# include <memory>
# include <string>

# include "fusion/emitter.cpp"

namespace example {

    class foo {

        private:
            std::string foo_name;

        public:
            explicit foo (const std::string& name) {
                foo_name = name;
            }

            std::string name () {
                return foo_name;
            }

            virtual void log () {
                std::cout << "this is { foo }" << std::endl;
            }
    };

    class bar : public foo {

        private:
            int bar_size;

        public:
            explicit bar (const std::string& name, int size) : foo(name) {
                bar_size = size;
            }

            int size () {
                return bar_size;
            }

            void log () override {
                std::cout << "this is { bar }" << std::endl;
            }
    };

    int run () {
        fusion::emitter<foo*> foo_emitter;

        foo_emitter.observe("hello").for_each([] (foo* x) {

        });

        foo_emitter.observe("world").cast<bar*>().for_each([] (bar* x) {

        });

        foo_emitter.emit("hello", new foo("your mom"));
        foo_emitter.emit("world", new bar("asdf", 69));

        return 0;
    }
}

int main () {
    return example::run();
}