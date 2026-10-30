#ifndef HOIHOI_MATH_MODULE_HPP
#define HOIHOI_MATH_MODULE_HPP

#include <algorithm>

#include "value/value.hpp"

namespace hoihoi {
    inline void addition_with_scalar(ObjectPtr& dst, const ObjectPtr& scalar) {
        if(!dst || !scalar)
            throw std::invalid_argument("None values");
        if(scalar->size() != 1)
            throw std::invalid_argument("You must have a scalar then one number");
        if(!scalar->inherence(Class::cluster) || !static_cast<Cluster*>(scalar.get())->at(0)->get_class()->inherence(Class::terminal_number)) 
            throw std::invalid_argument("You must have a scalar number and not and `" + scalar->get_class()->get_name() + "`");
        if(!dst->inherence(Class::cluster))
            throw std::invalid_argument("You must have a cluster");

        auto val_scal = static_cast<Cluster*>(scalar.get())->at(0);

        for(std::size_t i = 0UL; i < dst->size(); i++) {
            auto val = static_cast<Cluster*>(dst.get())->at(i);

            if(!val->inherence(Class::terminal_number)) 
                throw std::runtime_error("In your cluster, you must have only numbers");

            addition(val, val_scal);
        }
    }

    inline void addition_with_cluster(ObjectPtr& dst, const ObjectPtr& o) {
        if(!dst || !o)
            throw std::invalid_argument("None values");
        if(!dst->inherence(Class::cluster))
            throw std::invalid_argument("You must have a cluster for the first param");
        if(!o->inherence(Class::cluster))
            throw std::invalid_argument("You must have a cluster for the second param");
        if(dst->size() != o->size())
            throw std::invalid_argument("You must have the same size for these cluster");

        for(std::size_t i = 0UL; i < dst->size(); i++) {
            auto valA = static_cast<Cluster*>(dst.get())->at(i);
            auto valB = static_cast<Cluster*>(o.get())->at(i);

            if(!valA->inherence(Class::terminal_number)) throw std::runtime_error("In your cluster, you must have only numbers");
            if(!valB->inherence(Class::terminal_number)) throw std::runtime_error("In your cluster, you must have only numbers");

            addition(valA, valB);
        }
    }

    inline void sum(ObjectPtr& dst) {
        if(!dst)
            throw std::invalid_argument("None value");
        if(!dst->get_class()->inherence(Class::cluster))
            throw std::invalid_argument("You must have a cluster");

        auto values = static_cast<Cluster*>(dst.get())->get_values();

        auto sum = make_integer(0L);
        bool is_number = static_cast<Cluster*>(dst.get())->at(0)->inherence(Class::terminal_number);
        std::vector<ObjectPtr> res;

        for(auto it = values.begin(); it != values.end(); ++it) {
            if(is_number) {
                addition(sum, *it);
            } else if((*it)->inherence(Class::cluster)) {
                hoihoi::sum(*it);
                res.push_back(*it);
            } else {
                throw std::runtime_error("You must have only number");
            }
        }

        if(is_number) {
            dst = std::make_shared<Vector>(sum);
        } else {
            static_cast<Cluster*>(dst.get())->set_values(res);
        }
    }

    inline ObjectPtr range(double from, double to, double path) {
        std::vector<ObjectPtr> res;
        
        for(double val = std::abs(from); val < std::abs(to); val += path)
            res.push_back(std::make_shared<Vector>(make_float(val)));
        
        return std::make_shared<Vector>(std::move(res));
    }
    inline ObjectPtr range(double from, double to) { return range(from, to, 1.0); }
    inline ObjectPtr range(double to) { return range(0.0, to, 1.0); }

    inline ObjectPtr range(std::int64_t from, std::int64_t to, std::int64_t path) {
        std::vector<ObjectPtr> res;
        
        for(double val = std::abs(from); val < std::abs(to); val += path)
            res.push_back(std::make_shared<Vector>(make_integer(val)));
        
        return std::make_shared<Vector>(std::move(res));
    }
    inline ObjectPtr range(std::int64_t from, std::int64_t to) { return range(from, to, 1); }
    inline ObjectPtr range(std::int64_t to) { return range(0, to, 1); }
}

#endif /* HOIHOI_MATH_MODULE_HPP */
