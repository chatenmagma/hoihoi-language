#include "vm/runtime.hpp"
#include "vm/module.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace hoihoi;
using namespace std;

namespace fs = filesystem;

string Runtime::get_source(fs::path path) const {
    if(!fs::exists(path))
        throw invalid_argument("The file `" + path.string() + "` is not exist...");

    ifstream file(path);

    string source;
    string line;

    while(getline(file, line)) source += line + '\n';

    return source;
}

int Runtime::load_module(const string& path) {
    auto native_module = Module::get_native_module(path);

    if(native_module) {
        this->modules[path] = native_module;
        return 0;
    }

    this->modules[path] = make_shared<Module>(path);

    return this->modules[path]->state->execute(get_source(main_dir / (path + ".hoi")));
}

Runtime::Runtime() {
    this->init_attributes();
}

unordered_map<string, ObjectPtr> Runtime::get_init_global() {
    unordered_map<string, ObjectPtr> res;

    res.insert_or_assign("print", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        this->print(args);

        return nullptr;
    })));

    res.insert_or_assign("input", make_builtin([&](vector<ObjectPtr> args) -> ObjectPtr {
        this->print(args);

        std::string input;
        cin >> input;

        return make_shared<Vector>(make_shared<String>(input));
    }));

    res.insert_or_assign("int", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 2) throw overflow_error("You can have maximum two arguments (one");

        std::string base = "10";
        if(args.size() == 2) base = args[1]->to_string();

        return make_shared<Vector>(make_integer(std::stoll(args[0]->to_string(), nullptr, std::stoi(base))));
    })));

    res.insert_or_assign("float", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        return make_shared<Vector>(make_float(std::stod(args[0]->to_string())));
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

        return make_logical((args[0]->get_class()->inherence(res))? HOI_TERNARY_HIGH: HOI_TERNARY_HIGH);
    })));

    res.insert_or_assign("make_thing", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() > 1) throw runtime_error("You can only one argument max");
        if(args.empty())
            return make_shared<ClusterThing>();

        return make_shared<ClusterThing>(static_cast<size_t>(get_integer(args[0])));
    })));


    res.insert_or_assign("get_class_name", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 1) throw invalid_argument("You must have one argument");
        return args[0]->get_class()->get_attribute("__name__");
    })));

    res.insert_or_assign("untuple", make_builtin([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() != 1) throw invalid_argument("You must have one argument");
        if(!args[0]) throw invalid_argument("None value");

        auto cp = args[0]->copy();

        this->untuple(cp);

        return cp;
    }));

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

    Class::cluster->set_attribute("at", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 2) throw underflow_error("You must have two argument (one self and one argument)");
        if(args.size() > 2) throw overflow_error("You must have two argument (one self and one argument)");

        if(!args[0]->get_class()->inherence(Class::cluster))
            throw invalid_argument(format(
                "You cannot get at with a `{}`",
                args[0]->get_class()->get_name()
            ));

        return static_cast<Cluster*>(args[0].get())->at(args[1]->to_string());
    })));

    Class::cluster->set_attribute("front", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        if(!args[0]->get_class()->inherence(Class::cluster))
            throw invalid_argument(format(
                "You cannot get at with a `{}`",
                args[0]->get_class()->get_name()
            ));

        return static_cast<Cluster*>(args[0].get())->at(0);
    })));

    Class::cluster->set_attribute("back", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        if(!args[0]->get_class()->inherence(Class::cluster))
            throw invalid_argument(format(
                "You cannot get at with a `{}`",
                args[0]->get_class()->get_name()
            ));

        return static_cast<Cluster*>(args[0].get())->at(args[0]->size() - 1);
    })));

    Class::cluster->set_attribute("flatten", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");

        if(!args[0]->get_class()->inherence(Class::cluster))
            throw invalid_argument(format(
                "You cannot get at with a `{}`",
                args[0]->get_class()->get_name()
            ));

        vector<ObjectPtr> new_values = {};
        this->flatten(new_values, args[0]);
        
        auto res = static_cast<Cluster*>(args[0].get())->make_empty();
        static_cast<Cluster*>(res.get())->set_values(new_values);

        return res;
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

    Class::cluster->set_attribute("to_bag", make_shared<Terminal>(Class::terminal_builtin,
    make_shared<Builtin>([&](vector<ObjectPtr> args) -> ObjectPtr {
        if(args.size() < 1) throw underflow_error("You must have one argument");
        if(args.size() > 1) throw overflow_error("You must have one argument");
        
        if(auto* cluster = dynamic_cast<Cluster*>(args[0].get())) {
            return make_shared<Bag>(cluster->get_values(), cluster->is_negative());
        }

        throw invalid_argument(format(
            "You cannot convert to tuple with a `{}`",
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

void Runtime::print(const vector<ObjectPtr>& args) {
    for(size_t i = 0UL; i < args.size(); i++) {
        std::cout << args[i]->to_string();
        if(i < args.size() - 1) std::cout << " ";
    }

    std::cout << endl;
}

void Runtime::flatten(vector<ObjectPtr>& res, const ObjectPtr& obj) {
    if(obj->get_class()->inherence(Class::cluster)) {
        auto* cluster = static_cast<Cluster*>(obj.get());
        for(const auto& sub_obj: cluster->get_values())
            flatten(res, sub_obj);
    } else {
        res.push_back(obj);
    }
}

void Runtime::untuple(ObjectPtr& o) {
    if(!o)
        throw invalid_argument("None value");
    if(!o->inherence(Class::cluster))
        return;
    
    vector<ObjectPtr> values;

    for(auto& v: static_cast<Cluster*>(o.get())->get_values()) {
        untuple(v);
        values.push_back(v);
    }

    if(o->get_class() == Class::cluster_tuple)
        o = make_shared<Vector>(values);
    else
        static_cast<Cluster*>(o.get())->set_values(values);
}
