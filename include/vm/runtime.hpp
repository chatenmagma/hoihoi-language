#ifndef HOIHOI_RUNTIME_HPP
#define HOIHOI_RUNTIME_HPP

#include <filesystem>

#include "value/value.hpp"

namespace hoihoi {
    class Module;

    class Runtime {
        private:
            std::unordered_map<std::string, std::shared_ptr<Module>> modules;

            void print_ident(std::size_t indent);
            void print(const std::vector<ObjectPtr>& args);

            void flatten(std::vector<ObjectPtr>& res, const ObjectPtr& obj);

            std::string get_source(std::filesystem::path path) const;
            void untuple(ObjectPtr& obj);

            std::filesystem::path main_dir;
        public:
            Runtime();
            ~Runtime() = default;
            
            void init_attributes();
            int load_module(const std::string& path);
            inline std::shared_ptr<Module>& get_module(const std::string& name_module) { return modules.at(name_module); }

            void set_main_dir(std::filesystem::path main_dir) { this->main_dir = main_dir; }

            std::unordered_map<std::string, ObjectPtr> get_init_global();
    };
}

#endif /* HOIHOI_RUNTIME_HPP */
