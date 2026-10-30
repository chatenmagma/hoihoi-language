#ifndef HOIHOI_MODULE_HPP
#define HOIHOI_MODULE_HPP

#include "state.hpp"
#include "module/math_module.hpp"

#define HOI_MATH_MODULE_NAME "math"

namespace hoihoi {
    struct Module;

    using ModulePtr = std::shared_ptr<Module>;

    struct Module {
        std::string name;
        std::shared_ptr<State> state;

        static ModulePtr init_math_module();

        inline static ModulePtr math = init_math_module();

        inline static ModulePtr get_native_module(const std::string& name) {
            if(HOI_MATH_MODULE_NAME == name)
                return Module::math;

            return nullptr;
        }

        Module(std::string name)
            : name(std::move(name)), state(std::make_shared<State>(name, false)) {}
    };
}

#endif /* HOIHOI_MODULE_HPP */
