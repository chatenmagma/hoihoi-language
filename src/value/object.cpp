#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

Class::Class(const string& class_name, shared_ptr<Class> parent) {
    this->parent = parent.get();
    this->name = class_name;
}

shared_ptr<Class> Class::terminal = make_shared<Class>("terminal");
    shared_ptr<Class> Class::terminal_number = make_shared<Class>("num", Class::terminal);
        shared_ptr<Class> Class::terminal_integer = make_shared<Class>("int", Class::terminal_number);
        shared_ptr<Class> Class::terminal_float = make_shared<Class>("float", Class::terminal_number);
        
    shared_ptr<Class> Class::terminal_character = make_shared<Class>("char", Class::terminal);
    shared_ptr<Class> Class::terminal_logical = make_shared<Class>("log", Class::terminal);
    shared_ptr<Class> Class::terminal_builtin = make_shared<Class>("builtin", Class::terminal);
    shared_ptr<Class> Class::terminal_funtion = make_shared<Class>("function", Class::terminal);
    shared_ptr<Class> Class::terminal_thing = make_shared<Class>("thing", Class::terminal);
    shared_ptr<Class> Class::terminal_module = make_shared<Class>("module", Class::terminal);

shared_ptr<Class> Class::cluster = make_shared<Class>("cluster");
    shared_ptr<Class> Class::cluster_thing = make_shared<Class>("things", Class::cluster);
    shared_ptr<Class> Class::cluster_bag = make_shared<Class>("bag", Class::cluster);
        shared_ptr<Class> Class::cluster_set = make_shared<Class>("set", Class::cluster_bag);
        
    shared_ptr<Class> Class::cluster_vector = make_shared<Class>("vector", Class::cluster);
        shared_ptr<Class> Class::cluster_string = make_shared<Class>("str", Class::cluster_vector);
        shared_ptr<Class> Class::cluster_tuple = make_shared<Class>("tuple", Class::cluster_vector);

ObjectPtr Object::lower_operation(const ObjectPtr o) const {
    return make_shared<Terminal>(Class::terminal_logical, (size() < o->size())? HOI_TERNARY_HIGH: HOI_TERNARY_LOW);
}

ObjectPtr Object::greater_operation(const ObjectPtr o) const {
    return make_shared<Terminal>(Class::terminal_logical, (size() > o->size())? HOI_TERNARY_HIGH: HOI_TERNARY_LOW);
}
