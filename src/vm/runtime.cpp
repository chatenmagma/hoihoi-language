#include "vm/runtime.hpp"

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

    res.insert_or_assign("enumare", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        this->enumare(args[0]);

        return nullptr;
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

            return make_shared<ClusterOrdered>(res, cluster->is_negative());
        }

        throw invalid_argument(format(
            "You cannot split with a `{}`",
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
        if(args.size() < 2) throw underflow_error("You must have one argument");
        if(args.size() > 2) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            return cluster->pop();
        }

        throw invalid_argument(format(
            "You cannot pop with a `{}`",
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

void Runtime::enumare(const ObjectPtr o, size_t indent) {
    print_ident(indent);

    print({o});

    if(dynamic_cast<String*>(o.get())) return;

    if(auto* cluster = dynamic_cast<Cluster*>(o.get())) {
        for(const auto& v: cluster->get_values()) {
            enumare(v, indent + 2);
        }
    }
}
