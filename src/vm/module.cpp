#include "vm/module.hpp"
#include "value/value.hpp"

#include <cmath>

using namespace hoihoi;
using namespace std;

ModulePtr Module::init_math_module() {
    auto math = make_shared<Module>(HOI_MATH_MODULE_NAME);

    math->state->insert("pi", make_shared<Vector>(make_float(M_PI), false));
    math->state->insert("addition", make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 2) throw invalid_argument("You must have two arguments");
        
        auto cp = args[0]->copy();

        if(args[1]->size() == 1) {
            addition_with_scalar(cp, args[1]);
        } else {
            addition_with_cluster(cp, args[1]);
        }

        return cp;
    }));

    math->state->insert("lower", make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 2) throw invalid_argument("You must have two arguments");

        return make_logical(
            (get_float(args[0]) < get_float(args[1]))?
            HOI_TERNARY_LOW: HOI_TERNARY_HIGH
        );
    }));

    math->state->insert("greater", make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 2) throw invalid_argument("You must have two arguments");

        return make_logical(
            (get_float(args[0]) > get_float(args[1]))?
            HOI_TERNARY_HIGH: HOI_TERNARY_HIGH
        );
    }));

    math->state->insert("sum", make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
       if(args.size() != 1) throw invalid_argument("You must have one arguement");
       
       auto cp = args[0]->copy();

        sum(cp);

       return cp;
    }));

    math->state->insert("len",  make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
       if(args.size() != 1) throw invalid_argument("You must have one arguement");
        
       return make_shared<Vector>(make_integer(args[0]->size()), args[0]->is_negative());
    }));

    math->state->insert("range",  make_builtin([](vector<ObjectPtr> args) -> ObjectPtr {
       if(args.size() > 3) throw invalid_argument("You can have maximum 3 arguements");
       if(args.size() < 1) throw invalid_argument("You must have minimum one argument");

       if(args.size() == 1) {
            int64_t val_64 = get_integer(args[0]);
            double val = get_float(args[0]);
            
            return (static_cast<double>(val_64) == val)? range(val_64): range(val);
        }

        if(args.size() == 2) {
            auto from64 = get_integer(args[0]);
            auto to64 = get_integer(args[1]);

            auto from = get_float(args[0]);
            auto to = get_float(args[1]);

            return (
                (static_cast<double>(from64) == from) &&
                (static_cast<double>(to64) == to)
            )? range(from64, to64): range(from, to);
        }

        auto from64 = get_integer(args[0]);
        auto to64 = get_integer(args[1]);
        auto path64 = get_integer(args[2]);

        auto from = get_float(args[0]);
        auto to = get_float(args[1]);
        auto path = get_float(args[2]);

        return (
            (static_cast<double>(from64) == from) &&
            (static_cast<double>(to64) == to) &&
            (static_cast<double>(path64) == path)
        )? range(from64, to64, path64): range(from, to, path);
    }));

    return math;
}
