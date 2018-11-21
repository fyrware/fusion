# pragma once

# include <functional>
# include <vector>

namespace fusion {

    template <typename fill_type> class pool {

        private:
            std::function<fill_type()> pool_content_allocator;
            std::vector<fill_type> pool_contents;
            int pool_size;

        public:
            pool (const int size, const std::function<fill_type()> allocator) {
                pool_content_allocator = allocator;
                pool_size = 0;

                resize(size);
            }

            void resize (const int size) {
                if (pool_size > size) while (pool_contents.size() > size) {
                    pool_contents.pop_back();
                }
                else while (pool_contents.size() < size) {
                    pool_contents.emplace_back(pool_content_allocator());
                }

                pool_size = size;
            }

            int size () {
                return pool_size;
            }
    };
}