#include "value/value.hpp"
#include "utils/formatter.hpp"

#include <random>

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
    return (is_low()? "-(": "(") + vector_to_print(values) + ")";
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
    if(!o->get_class()->inherence(Class::cluster)) throw invalid_argument(format(
        "You cannot add with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = static_cast<Cluster*>(o.get())->get_values();

    if(is_neutral() || (get_logical() == o->get_logical())) { // same signed 
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

void Cluster::mul(const ObjectPtr o) {
    if(!o->get_class()->inherence(Class::cluster)) 
        throw invalid_argument(format(
            "You cannot sub with a `{}` with `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));

    if(is_neutral() || o->is_neutral()) 
        return this->clear();
        
    auto other_values = static_cast<Cluster*>(o.get())->get_values();

    vector<ObjectPtr> new_values;
    vector<ObjectPtr> res;

    for(auto it = begin(); it != end(); ++it) {
        for(size_t j = 0UL; j < o->size(); j++) {
            if((*it)->get_class() == Class::cluster_tuple) {
                auto tuple_val = static_cast<Tuple*>((*it).get())->get_values();

                res.insert(res.end(), tuple_val.begin(), tuple_val.end());
                res.push_back(other_values.at(j));
            } else {
                res.push_back(*it);
                res.push_back(other_values.at(j));
            }
            new_values.push_back(
                make_shared<Tuple>(res)
            );
            res.clear();
        }
    }

    this->set_values(new_values);
}

void Cluster::div(const ObjectPtr o) {
    if(!o->get_class()->inherence(Class::cluster)) 
        throw invalid_argument(format(
            "You cannot sub with a `{}` with `{}`",
            get_class()->get_name(),
            o->get_class()->get_name()
        ));
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

        if((v->get_class() == Class::cluster_string) || (v->get_class() == Class::terminal_character)) {
            res += str_to_print(v->to_string());
        } else if(is_high() && v->size() == 1UL && (v->get_class() == Class::cluster_vector)) {
            Vector* tmp = static_cast<Vector*>(v.get());

            if((tmp->at(0)->get_class() == Class::cluster_string) || (tmp->at(0)->get_class() == Class::terminal_character))
                res += (tmp->is_low())? "-[": "[" + str_to_print(tmp->to_string()) + "]";
            else res += tmp->to_string();
        } else {
            res += v->to_string();
        }
        if(i < size() - 1) res += ", ";
    }

    return res + "]";
}

// BAG

ObjectPtr Bag::at(size_t index) const {
    if(index >= values.size()) throw std::out_of_range("Index out of range");

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<size_t> dist(0, values.size() - 1);

    auto it = values.begin();
    advance(it, dist(generator));

    return *it;
}

ObjectPtr Bag::pop() {
    if(values.empty()) throw std::invalid_argument("You cannot pop from an empty bag");

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<size_t> dist(0, values.size() - 1);

    auto it = values.begin();
    advance(it, dist(generator));

    ObjectPtr val = *it;
    values.erase(it);

    return val;
}

bool Bag::equal(const ObjectPtr o) const {
    if(this == o.get()) return true;
    // check if has the same size and they are the same typed
    if((get_class() != o->get_class()) || (size() != o->size()))
        return false;

    auto other_values = static_cast<Bag*>(o.get())->values;

    for(const auto& v: values) {
        if(find_if(other_values.begin(), other_values.end(), [&v](const ObjectPtr& o_v) { 
            return o_v->equal(v); 
        }) == other_values.end()) return false;
    }

    return true;
}

vector<ObjectPtr> Bag::get_values() const {
    vector<ObjectPtr> res = vector<ObjectPtr>(values.begin(), values.end());

    random_device rd;
    mt19937 generator(rd());

    shuffle(res.begin(), res.end(), generator);

    return res;
}

void Bag::add(const ObjectPtr o) {
    if(o->get_class()->inherence(Class::cluster)) throw invalid_argument(format(
        "You cannot add with a `{}` with `{}`",
        get_class()->get_name(),
        o->get_class()->get_name()
    ));

    auto other_values = static_cast<Cluster*>(o.get())->get_values();

    if(is_neutral() || (get_logical() == o->get_logical())) { // same signed 
        values.insert(values.end(), other_values.begin(), other_values.end());
    } else {
        if(size() <= o->size()) {
            opposite();
            
            other_values.erase(other_values.begin(), other_values.begin() + size());
            values = other_values;
        } else {
            for(size_t i = 0UL; i < o->size(); i++) { pop(); }
        }
    }
}

void Bag::sub(const ObjectPtr o) {
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
            for(size_t i = 0UL; i < o->size(); i++) { pop(); }
        }
    }
}

void Bag::replace(size_t, ObjectPtr o) {
    random_device rd;
    mt19937 genenator(rd());

    uniform_int_distribution<size_t> dist(0, size() - 1);

    values[dist(genenator)] = o;
}

string Bag::to_string() const {
    return (is_low()? "-{": "{") + vector_to_print(get_values())  + "}";
}
