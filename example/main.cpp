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
    };

    class bar : public foo {

        private:
            int bar_size;

        public:
            explicit bar (const std::string& name, int size) : foo(name) {
                bar_size = size;
            }
    };

    int run () {
        fusion::executor thread_pool(3);
        fusion::emitter<foo*> foo_emitter;

        foo_emitter.observe("foo").use_executor(thread_pool).for_each([ & ] (foo* x) {
            std::cout << "foo" << std::endl;
            foo_emitter.emit("hello", new foo("your mom"));
        });

        foo_emitter.observe("hello").use_executor(thread_pool).for_each([ & ] (foo* x) {
            std::cout << "hello" << std::endl;
            foo_emitter.emit("world", new bar("asdf", 1234));
        });

        foo_emitter.observe("world").use_executor(thread_pool).cast<bar*>().for_each([] (bar* x) {
            std::cout << "world" << std::endl;
        });

        foo_emitter.emit("foo", new foo("foo"));

        thread_pool.terminate();
        thread_pool.flush();

        return 0;
    }
}

int main () {
    return example::run();
}