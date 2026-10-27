#include "vm/runtime.hpp"

#include <algorithm>
#include <iostream>

using namespace hoihoi;
using namespace std;

unordered_map<string, ObjectPtr> Runtime::get_init_global() {
    unordered_map<string, ObjectPtr> res;

    res.insert_or_assign("print", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        this->print(args);

        return nullptr;
    })));

    res.insert_or_assign("inherence", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 2) throw invalid_argument("Need 2 arguments");
        if(args[1]->get_class() != Class::cluster_vector) 
            throw invalid_argument("the second argument must is a " + Class::cluster_vector->get_name());

        shared_ptr<Class> res;
        if(Class::terminal->get_name() == args[1]->to_string())
            res = Class::terminal;
        else if(Class::cluster->get_name() == args[1]->to_string())
            res = Class::cluster;
        else if(Class::cluster_vector->get_name() == args[1]->to_string())
            res = Class::cluster_vector;
        else if(Class::cluster_string->get_name() == args[1]->to_string())
            res = Class::cluster_string;
        else if(Class::cluster_tuple->get_name() == args[1]->to_string())
            res = Class::cluster_tuple;
        else if(Class::cluster_thing->get_name() == args[1]->to_string())
            res = Class::cluster_thing;
        else
            throw invalid_argument("the second agument, " + args[1]->to_string() + " is not a class defined");

        return make_logical((args[0]->get_class()->inherence(res))? TernaryLogical::HIGH: TernaryLogical::LOW);
    })));

    res.insert_or_assign("make_thing", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() > 1) throw runtime_error("You can only one argument max");
        if(args.empty())
            return make_shared<ClusterThing>();
        
        auto* term = dynamic_cast<Terminal*>(args[0].get());
        if(!term || (!holds_alternative<int64_t>(term->get_value()) && !holds_alternative<double>(term->get_value()))) 
            throw runtime_error("You must have interger or float");
        if(holds_alternative<int64_t>(term->get_value()))
            return make_shared<ClusterThing>(static_cast<size_t>(get<int64_t>(term->get_value())));
        return make_shared<ClusterThing>(static_cast<size_t>(get<double>(term->get_value())));
    })));


    res.insert_or_assign("get_class_name", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 1) throw invalid_argument("You must have one argument");
        return args[0]->get_class()->get_attribute("__name__");
    })));

    return res;
}

void Runtime::init_attributes() {
    Class::cluster->set_attribute("split", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            auto cA = cluster->make_empty();
            auto cB = cluster->make_empty();

            size_t i = 0UL;
            for(; i < cluster->size() / 2; i++)
                cA->push(cluster->at(i));
            for(; i < cluster->size(); i++)
                cB->push(cluster->at(i));
            
            if(cluster->is_negative()) {
                cA->opposite();
                cB->opposite();
            }
            vector<ObjectPtr> res = { cA, cB };

            return make_shared<Vector>(res, cluster->is_negative());
        }

        throw invalid_argument(format(
            "You cannot split with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster_vector->set_attribute("reverse", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 1) throw invalid_argument("You must have one self");

        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            auto values = cluster->get_values();
            reverse(values.begin(), values.end());
            cluster->set_values(values);

            return nullptr;
        }

        throw invalid_argument(format(
            "You cannot reverse with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));
    

    Class::cluster->set_attribute("push", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 2) throw underflow_error("You must have two argument (one self and one argument)");
        if(args.size() > 2) throw overflow_error("You must have two argument (one self and one argument)");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            cluster->push(args[1]);
        }

        throw invalid_argument(format(
            "You cannot push with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster->set_attribute("pop", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            return cluster->pop();
        }

        throw invalid_argument(format(
            "You cannot pop with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster->set_attribute("clear", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            cluster->clear();
            return nullptr;
        }

        throw invalid_argument(format(
            "You cannot clear with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster->set_attribute("to_tuple", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            return make_shared<Tuple>(cluster->get_values(), cluster->is_negative());
        }

        throw invalid_argument(format(
            "You cannot convert to tuple with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster_string->set_attribute("to_int", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 2) throw overflow_error("You can have maximum two arguments (one");

        std::string base = "10";
        if(args.size() == 2) base = args[1]->to_string();

        if(auto* str = dynamic_cast<String*>(args[0].get())) {
            return std::make_shared<Terminal>(Class::terminal_integer, std::stoll(str->value, nullptr, std::stoi(base)));
        }

        throw invalid_argument(format(
            "You cannot convert to integer with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster_string->set_attribute("to_float", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        if(auto* str = dynamic_cast<String*>(args[0].get())) {
            return std::make_shared<Terminal>(Class::terminal_float, std::stod(str->value));
        }

        throw invalid_argument(format(
            "You cannot convert to float with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));

    Class::cluster->set_attribute("to_thing", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            return make_shared<ClusterThing>(cluster->size(), cluster->is_negative());
        }

        throw invalid_argument(format(
            "You cannot convert to thing with a `{}`",
            args[0]->get_class()->get_name()
        ));
    })));
}

void Runtime::print_ident(size_t indent) { for(size_t i = 0UL; i < indent; i++) cout << " "; }

void Runtime::print(vector<ObjectPtr> args) {
    for(size_t i = 0UL; i < args.size(); i++) {
        std::cout << args[i]->to_string();
        if(i < args.size() - 1) std::cout << " ";
    }

    std::cout << endl;
}
