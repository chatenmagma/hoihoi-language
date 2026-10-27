#ifndef HOIHOI_RUNTIME_HPP
#define HOIHOI_RUNTIME_HPP

#include "value/value.hpp"

namespace hoihoi {
    class Runtime {
        private:
            void print_ident(std::size_t indent);
            void print(std::vector<ObjectPtr> args);
        public:
            Runtime() { init_attributes(); }
            ~Runtime() = default;
            
            void init_attributes();

            std::unordered_map<std::string, ObjectPtr> get_init_global();
    };
}

#endif /* HOIHOI_RUNTIME_HPP */
