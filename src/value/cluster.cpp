#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

// String

ObjectPtr String::at(std::size_t i) const {
    return make_shared<Terminal>(Class::terminal_character, value.at(i), negative);
}

void String::push(ObjectPtr o) {
    if(auto* str = dynamic_cast<String*>(o.get())) {
        value += str->value;
        return;
    } else if(auto* terminal = dynamic_cast<Terminal*>(o.get())) {
        if(holds_alternative<char>(terminal->get_value())) {
            value += get<char>(terminal->get_value());
            return;
        }
    }

    throw invalid_argument(format(
        "You cannot push a `{}` into `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));
}

ObjectPtr String::pop() {
    auto val = value.back();
    value.pop_back();

    return make_shared<Terminal>(Class::terminal_character, val, negative);
}

vector<ObjectPtr> String::get_values() const {
    vector<ObjectPtr> res;

    for(auto c: value)
        res.push_back(make_shared<Terminal>(Class::terminal_character, c, negative));

    return res;
}

void String::assign(const ObjectPtr o) {
    negative = o->is_negative();
    
    if(auto* str = dynamic_cast<String*>(o.get())) {
        value = str->value;
        return;
    } else if(auto* terminal = dynamic_cast<Terminal*>(o.get())) {
        if(holds_alternative<char>(terminal->get_value())) {
            value = string(1, get<char>(terminal->get_value()));
            return;
        }
    }

    throw invalid_argument(format(
        "You cannot assign a `{}` into `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));
}

// Ordered

void ClusterOrdered::assign(const ObjectPtr o) {
    if(auto ordered = dynamic_cast<ClusterOrdered*>(o.get())) {
        this->values = ordered->values;
        this->negative = ordered->negative;
    } else {
        throw invalid_argument(format(
            "You cannot assign with a `{}` into `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));
    }
}

bool ClusterOrdered::equal(const ObjectPtr o) const {
    if(this == o.get()) return true;
    if(size() != o->size()) return false;

    if(auto* ordered = dynamic_cast<ClusterOrdered*>(o.get())) {
        for(size_t i = 0UL; i < ordered->size(); i++)
            if(!this->at(i)->equal(ordered->at(i))) return false;
        
        return true;
    }
    
    return false;
}

void ClusterOrdered::add(const ObjectPtr o) {
    auto cluster = dynamic_cast<Cluster*>(o.get());

    if(!cluster) throw invalid_argument(format(
        "You cannot add with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = cluster->get_values();

    if(is_neutral() || (get_logical() == cluster->get_logical())) { // same signed 
        values.insert(values.end(), other_values.begin(), other_values.end());
    } else {
        if(size() <= cluster->size()) {
            opposite();
            
            other_values.erase(other_values.begin(), other_values.begin() + size());
            values = other_values;
        } else {
            values.erase(values.end() - cluster->size(), values.end());
        }
    }
}

void ClusterOrdered::sub(const ObjectPtr o) {
    auto cluster = dynamic_cast<Cluster*>(o.get());

    if(!cluster) throw invalid_argument(format(
        "You cannot sub with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = cluster->get_values();

    if(!is_neutral() && (get_logical() != cluster->get_logical())) { // same signed 
        values.insert(values.end(), other_values.begin(), other_values.end());
    } else {
        if(size() <= cluster->size()) {
            opposite();
            
            other_values.erase(other_values.begin(), other_values.begin() + size());
            values = other_values;
        } else {
            values.erase(values.end() - cluster->size(), values.end());
        }
    }
}

void ClusterOrdered::mul(const ObjectPtr o) {
    auto cluster = dynamic_cast<Cluster*>(o.get());

    if(!cluster) throw invalid_argument(format(
        "You cannot mul with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = cluster->get_values();
}

void ClusterOrdered::div(const ObjectPtr o) {
    auto cluster = dynamic_cast<Cluster*>(o.get());

    if(!cluster) throw invalid_argument(format(
        "You cannot div with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = cluster->get_values();
}

