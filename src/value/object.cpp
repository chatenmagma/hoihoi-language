#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

Class::Class(const string& class_name, shared_ptr<Class> parent) {
    this->parent = parent;
    set_attribute("__name__", make_shared<String>(class_name));
}

string Class::get_name() const { return get_attribute("__name__")->to_string(); }

shared_ptr<Class> Class::terminal = make_shared<Class>("terminal");
    shared_ptr<Class> Class::terminal_character = make_shared<Class>("char", Class::terminal);
    shared_ptr<Class> Class::terminal_logical = make_shared<Class>("log", Class::terminal);
    shared_ptr<Class> Class::terminal_builtin = make_shared<Class>("builtin", Class::terminal);
    shared_ptr<Class> Class::terminal_funtion = make_shared<Class>("function", Class::terminal);

shared_ptr<Class> Class::cluster = make_shared<Class>("cluster");
    shared_ptr<Class> Class::cluster_string = make_shared<Class>("str", Class::cluster);
    shared_ptr<Class> Class::cluster_ordered = make_shared<Class>("ordered", Class::cluster);


ObjectPtr Object::lower_operation(const ObjectPtr o) const {
    return make_shared<Terminal>(Class::terminal_logical, (size() < o->size())? TernaryLogical::HIGH: TernaryLogical::LOW);
}

ObjectPtr Object::greater_operation(const ObjectPtr o) const {
    return make_shared<Terminal>(Class::terminal_logical, (size() > o->size())? TernaryLogical::HIGH: TernaryLogical::LOW);
}
