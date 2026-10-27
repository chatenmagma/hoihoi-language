#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

// ClusterThing

ObjectPtr ClusterThing::at(size_t) const { return (negative)? Terminal::negative_thing : Terminal::positive_thing; }
ObjectPtr ClusterThing::pop() {
    if(values == 0UL) throw std::invalid_argument("You cannot pop from an empty cluster");
    values--;

    return make_thing(negative);
}

vector<ObjectPtr> ClusterThing::get_values() const {
    return vector<ObjectPtr>(values, make_thing(negative));
}

// Tuple

bool Tuple::equal(const ObjectPtr o) const {
    if(this == o.get()) return true;
    // check if has the same size and they are the same typed
    if((get_class() != o->get_class()) || (size() != o->size())) return false;

    for(size_t i = 0UL; i < o->size(); i++)
        if(!this->at(i)->equal(static_cast<Tuple*>(o.get())->at(i))) return false;
        
    return true;
    
}

string Tuple::to_string() const {
    string res = (is_low())? "-(": "(";

    for(size_t i = 0UL; i < values.size(); i++) {
        if(values[i]->get_class() == Class::cluster_string)
            res += "\"" + values[i]->to_string() + "\"";
        else if(values[i]->get_class() == Class::terminal_character)
            res += "\'" + values[i]->to_string() + "\'";
        else 
            res += values[i]->to_string();
        if(i < values.size() - 1) res += ", ";
    }

    res += ")";

    return res;
}

// String

ObjectPtr String::at(std::size_t i) const {
    return make_shared<Terminal>(Class::terminal_character, value.at(i), negative);
}

void String::push(ObjectPtr o) {
    if(o->get_class() == Class::cluster_string) {
        value += static_cast<String*>(o.get())->value;
        return;
    } else if(o->get_class() == Class::terminal_character) {
        value += get<char>(static_cast<Terminal*>(o.get())->get_value());
        return;
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

    return make_character(val, negative);
}

vector<ObjectPtr> String::get_values() const {
    vector<ObjectPtr> res;

    for(auto c: value)
        res.push_back(make_character(c, negative));

    return res;
}

// Ordered

bool Vector::equal(const ObjectPtr o) const {
    if(this == o.get()) return true;
    // check if has the same size and they are the same typed
    if((get_class() != o->get_class()) || (size() != o->size()))
        return false;

    for(size_t i = 0UL; i < o->size(); i++)
        if(!this->at(i)->equal(static_cast<Vector*>(o.get())->at(i))) return false;
        
    return true;
}

void Vector::add(const ObjectPtr o) {
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

void Vector::sub(const ObjectPtr o) {
    if(!o->get_class()->inherence(Class::cluster)) 
        throw invalid_argument(format(
            "You cannot sub with a `{}` with `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));

    auto other_values = static_cast<Cluster*>(o.get())->get_values();

    if(!is_neutral() && (get_logical() != o->get_logical())) { // same signed 
        values.insert(values.end(), other_values.begin(), other_values.end());
    } else {
        if(size() <= o->size()) {
            opposite();
            
            other_values.erase(other_values.begin(), other_values.begin() + size());
            values = other_values;
        } else {
            values.erase(values.end() - o->size(), values.end());
        }
    }
}

void Vector::mul(const ObjectPtr o) {
    if(!o->get_class()->inherence(Class::cluster)) 
        throw invalid_argument(format(
            "You cannot sub with a `{}` with `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));

    if(is_neutral() || o->is_neutral()) 
        return values.clear();
        
    auto other_values = static_cast<Cluster*>(o.get())->get_values();

    vector<ObjectPtr> new_values;
    vector<ObjectPtr> res;

    for(size_t i = 0UL; i < size(); i++) {
        for(size_t j = 0UL; j < o->size(); j++) {
            if(values.at(i)->get_class() == Class::cluster_tuple) {
                auto tuple_val = static_cast<Tuple*>(values.at(i).get())->get_values();

                res.insert(res.end(), tuple_val.begin(), tuple_val.end());
                res.push_back(other_values.at(j));
            } else {
                res.push_back(values.at(i));
                res.push_back(other_values.at(j));
            }
            new_values.push_back(
                make_shared<Tuple>(res)
            );
            res.clear();
        }
    }

    values = new_values;
}

void Vector::div(const ObjectPtr o) {
    if(!o->get_class()->inherence(Class::cluster)) 
        throw invalid_argument(format(
            "You cannot sub with a `{}` with `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));

    if(o->is_neutral()) return;

    auto other_values = static_cast<Cluster*>(o.get())->get_values();
    vector<ObjectPtr> new_values;
    vector<ObjectPtr> res;

    for(size_t i = 0UL; i < size(); i++) {
        if(values.at(i)->get_class() != Class::cluster_tuple)
            throw runtime_error("You cannot divide because you need a " + Class::cluster_tuple->get_name());

        Tuple* tuple = static_cast<Tuple*>(values.at(i).get());

        for(size_t j = 0UL; j < tuple->size(); j++) {
            bool can_add = true;
            for(size_t k = 0UL; k < o->size(); k++) {
                if(tuple->at(j)->equal(other_values.at(i))) {
                    can_add = false;
                }
            }

            if(can_add) res.push_back(tuple->at(j));
            can_add = false;
        }

        ObjectPtr t = make_shared<Tuple>(res);

        if(find_if(new_values.begin(), new_values.end(), [&t](const ObjectPtr& o_v) { 
            return o_v->equal(t); 
        }) == new_values.end()) {
            new_values.push_back(t);
        }
        res.clear();
    }

    values = new_values;
}


string Vector::to_string() const {
    if(is_high() && size() == 1 && (
        values.at(0)->get_class() == Class::cluster_string ||
        values.at(0)->get_class()->inherence(Class::terminal))
    ) 
        return values.at(0)->to_string();
    
    string res = (is_low())? "-[": "[";

    for(size_t i = 0UL; i < size(); i++) {
        const auto& v = values.at(i);

        if(v->get_class() == Class::cluster_string) {
            res += "\"" + v->to_string() + "\"";
        } else if(v->get_class() == Class::terminal_character) {
            res += "\'" + v->to_string() + "\'";
        } else if(is_high() && v->size() == 1UL && (v->get_class() == Class::cluster_vector)) {
            Vector* tmp = static_cast<Vector*>(v.get());

            if(tmp->at(0)->get_class() == Class::cluster_string)
                res += (tmp->is_low())? "-[\"": "[\"" + tmp->to_string() + "\"]";
            else {
                res += (tmp->is_low())? "-[\'": "[\"" + tmp->to_string() + "\']";
            }
        } else {
            res += v->to_string();
        }
        if(i < size() - 1) res += ", ";
    }

    return res + "]";
}
