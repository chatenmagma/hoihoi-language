#ifndef HOIHOI_CLUSTER_HPP
#define HOIHOI_CLUSTER_HPP

#include <iterator>
#include <vector>
#include <unordered_set>

#include "cluster_iterator.hpp"
#include "terminal.hpp"

#include "object.hpp"

namespace hoihoi {
    class Cluster: public Object {
        public:
            using iterator = ClusterIterator;
            using const_iterator = ClusterConstIterator;

            Cluster(std::shared_ptr<Class> klass)
                : Object(klass) {}
            Cluster(std::shared_ptr<Class> klass, bool negative)
                : Object(klass, negative) {}
            virtual ~Cluster() override = default;

            virtual ObjectPtr or_operation(const ObjectPtr other) const override {
                throw std::invalid_argument(std::format(
                    "You cannot or with a `{}` with `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }
            virtual ObjectPtr and_operation(const ObjectPtr other) const override {
                throw std::invalid_argument(std::format(
                    "You cannot and with a `{}` with `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            inline bool one_string() const noexcept { 
                return size() == 1UL && (at(0)->get_class() == Class::cluster_string); 
            }
            inline bool one_terminal() const noexcept {
                return size() == 1UL && (at(0)->get_class()->inherence(Class::terminal));
            }
            inline bool one_character() const noexcept {
                return size() == 1UL && (at(0)->get_class() == Class::terminal_character);
            }

            virtual std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const = 0;
            virtual std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const = 0;

            virtual ObjectPtr at(const std::string& key) const = 0;
            virtual ObjectPtr at(std::size_t index) const = 0;

            virtual void replace(const std::string& key, ObjectPtr object) = 0;
            virtual void replace(const std::size_t key, ObjectPtr object) = 0;

            virtual iterator begin() = 0;
            virtual iterator end() = 0;
            virtual const_iterator begin() const = 0;
            virtual const_iterator end() const = 0;

            virtual void clear() = 0;

            virtual void push(ObjectPtr other) = 0;
            virtual ObjectPtr pop() = 0;

            virtual void reserve(std::size_t reserve) = 0;

            virtual std::vector<ObjectPtr> get_values() const = 0;
            virtual void set_values(std::vector<ObjectPtr> n_values) = 0;

            virtual void mul(const ObjectPtr other) override;
            virtual void div(const ObjectPtr other) override;
    };

    class ClusterThing final: public Cluster {
        private:
            std::size_t values;
        public:
            ClusterThing()
                : Cluster(Class::cluster_thing), values(0UL) {}
            ClusterThing(bool negative)
                : Cluster(Class::cluster_thing, negative), values(0UL) {}
            ClusterThing(std::size_t values, bool negative = false)
                : Cluster(Class::cluster_thing, negative), values(values) {}
            ClusterThing(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_thing, negative), values(values.size()) {}
            ~ClusterThing() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t) const override {
                return std::make_shared<ClusterThing>();
            }
            std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const override {
                return std::make_shared<ClusterThing>(values.size());
            }

            ObjectPtr at(const std::string& key) const override { return at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override;

            void replace(const std::string&, ObjectPtr) override {}
            void replace(std::size_t, ObjectPtr) override {}

            iterator begin() override {
                auto val = make_thing(is_negative());
                return iterator::repeated(val, 0UL, values); 
            }
            iterator end() override {
                auto val = make_thing(is_negative());
                return iterator::repeated(val, values, values);
            }

            const_iterator begin() const override {
                auto val = make_thing(is_negative());
                return const_iterator::repeated(val, 0UL, values); 
            }
            const_iterator end() const override {
                auto val = make_thing(is_negative());
                return const_iterator::repeated(val, values, values);
            }

            void push(ObjectPtr) override { values++; };
            ObjectPtr pop() override;

            void clear() override { values = 0UL; }
            void reserve(std::size_t) override {}

            std::vector<ObjectPtr> get_values() const override;
            void set_values(std::vector<ObjectPtr> new_values) override { this->values = new_values.size(); }

            // ====== OBJECT METHOD ======

            ObjectPtr copy() const override { return std::make_shared<ClusterThing>(values, negative); }

            bool equal(const ObjectPtr other) const override {
                if(this == other.get()) return true;

                if(auto* cluster_thing = dynamic_cast<ClusterThing*>(other.get()))
                    return values == cluster_thing->values;

                return false;
            }

            void add(const ObjectPtr other) override {
                if(is_neutral() || get_logical() == other->get_logical())
                    values += other->size();
                else if(other->size() > values) {
                    values = other->size() - values;
                    opposite();
                } else {
                    values -= other->size();
                }
            }

            void sub(const ObjectPtr other) override {
                if(get_logical() != other->get_logical()) {
                    values += other->size();
                    if(is_neutral() && other->is_high())
                        negative = true;
                } else if(other->size() > values) {
                    values = other->size() - values;
                    opposite();
                } else {
                    values -= other->size();
                }
            }

            void mul(const ObjectPtr other) override {
                values *= other->size();

                if(get_logical() != other->get_logical()) opposite();
                else if(get_logical() == HOI_TERNARY_LOW && other->get_logical() == HOI_TERNARY_LOW) opposite();
            }

            void div(const ObjectPtr other) override {
                if(other->size() == 0UL) throw std::invalid_argument("You cannot divide by zero");

                values /= other->size();

                if(get_logical() != other->get_logical()) opposite();
                else if(get_logical() == HOI_TERNARY_LOW && other->get_logical() == HOI_TERNARY_LOW) opposite();
            }

            std::size_t size() const override { return values; }
            std::size_t hash() const override { return std::hash<std::size_t>()(values); }

            std::string to_string() const override {
                return std::format(
                    "<{} cluster_things with {} elements>",
                    hoihoi::to_string(get_logical()),
                    values
                );
            }
    };

    class Tuple final: public Cluster {
        private:
            std::vector<ObjectPtr> values;
        public:
            Tuple()
                : Cluster(Class::cluster_tuple) {}
            Tuple(bool negative)
                : Cluster(Class::cluster_tuple, negative) {}
            Tuple(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_tuple, negative), values(std::move(values)) {}
            ~Tuple() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t) const override {
                return std::make_shared<Tuple>();
            }
            std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const override {
                return std::make_shared<Tuple>(std::move(values));
            }

            ObjectPtr at(const std::string& key) const override { return values.at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override { return values.at(index); }

            void replace(const std::string& key, ObjectPtr o) override { replace(std::stoul(key), std::move(o)); }
            void replace(std::size_t index, ObjectPtr o) override { values[index] = o; }

            iterator begin() override { return iterator(values.begin()); }
            iterator end() override { return iterator(values.end()); }
            const_iterator begin() const override { return const_iterator(values.begin()); }
            const_iterator end() const override { return const_iterator(values.end()); }

            void push(ObjectPtr) override { throw std::runtime_error("You cannot push to a tuple"); };
            ObjectPtr pop() override { throw std::runtime_error("You cannot pop from a tuple"); };

            void clear() override { throw std::runtime_error("You cannot clear a tuple"); }
            void reserve(std::size_t) override { throw std::runtime_error("You cannot reserve space in a tuple"); }

            std::vector<ObjectPtr> get_values() const override { return values; }
            void set_values(std::vector<ObjectPtr>) override { throw std::runtime_error("You cannot set new values in a tuple"); }

            // ====== OBJECT METHOD =======

            ObjectPtr copy() const override { return std::make_shared<Tuple>(values, negative); }

            bool equal(const ObjectPtr other) const override;

            void add(const ObjectPtr) override { throw std::runtime_error("You cannot add to a tuple"); }
            void sub(const ObjectPtr) override { throw std::runtime_error("You cannot subtract from a tuple"); }
            void mul(const ObjectPtr) override { throw std::runtime_error("You cannot multiply a tuple"); }
            void div(const ObjectPtr) override { throw std::runtime_error("You cannot divide a tuple"); }

            std::string to_string() const override;

            std::size_t size() const override { return values.size(); }
            std::size_t hash() const override {
                std::size_t seed = 0UL;
                for(const auto& obj: values) {
                    seed ^= obj->hash() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
                return seed;
            }
    };

    class String final: public Cluster {
        public:
            std::string value;
        public:
            String(bool negative = false)
                : Cluster(Class::cluster_string, negative) {}
            String(const std::string& value, bool negative = false)
                : Cluster(Class::cluster_string, negative), value(value) {}
            String(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_string, negative) {
                    for(const auto& obj: values) value += obj->to_string();
                }
            ~String() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<String>();
                tmp->reserve(reserve);

                return tmp;
            }
            std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const override {
                return std::make_shared<String>(std::move(values));
            }

            ObjectPtr at(const std::string& key) const override { return at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override;

            void replace(const std::string&, ObjectPtr) override { throw std::invalid_argument("You cannot replace from str"); }
            void replace(std::size_t, ObjectPtr) override { throw std::invalid_argument("You cannot replace from str"); }

            iterator begin() override { return iterator::character(value.begin(), value.end()); }
            iterator end() override { return iterator::character(value.end(), value.end()); }
            const_iterator begin() const override { return const_iterator::character(value.begin(), value.end()); }
            const_iterator end() const override { return const_iterator::character(value.cend(), value.cend()); }

            void push(ObjectPtr other) override;
            ObjectPtr pop() override;

            void clear() override { value.clear(); }
            void reserve(std::size_t reserve) override { value.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override;
            void set_values(std::vector<ObjectPtr> new_values) override {
                std::string res;
                for(const auto& o: new_values) res += o->to_string();
                this->value = res;
            }

            // ====== OBJECT METHOD ======

            ObjectPtr copy() const override { return std::make_shared<String>(std::move(value), negative); }

            bool equal(const ObjectPtr other) const override {
                if(this == other.get()) return true;

                if(auto* str = dynamic_cast<String*>(other.get()))
                    return value == str->value;

                return false;
            }

            void add(const ObjectPtr other) override {
                if(is_neutral() || get_logical() == other->get_logical())
                    value += other->to_string();
                else {
                    throw std::invalid_argument(std::format(
                        "You cannot add with a `{}` with `{}` when the signed is not same",
                        get_class()->get_name(),
                        other->get_class()->get_name()
                    ));
                }
            }
            void sub(const ObjectPtr other) override {
                throw std::invalid_argument(std::format(
                    "You cannot sub with a `{}` with `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }
            void mul(const ObjectPtr other) override {
                throw std::invalid_argument(std::format(
                    "You cannot mul with a `{}` with `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }
            void div(const ObjectPtr other) override {
                throw std::invalid_argument(std::format(
                    "You cannot div with a `{}` with `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            std::string to_string() const override { return value; }

            std::size_t size() const override { return value.size(); }
            std::size_t hash() const override { return std::hash<std::string>()(value); }
    };

    class Vector: public Cluster {
        private:
            std::vector<ObjectPtr> values;
        public:
            Vector()
                : Cluster(Class::cluster_vector) {}
            Vector(bool negative)
                : Cluster(Class::cluster_vector, negative) {}
            Vector(ObjectPtr object, bool negative = false)
                : Cluster(Class::cluster_vector, negative) { this->values.push_back(object); }
            Vector(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_vector, negative), values(std::move(values)) {}
            ~Vector() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<Vector>();
                tmp->reserve(reserve);

                return tmp;
            }
            std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const override {
                return std::make_shared<Vector>(std::move(values));
            }

            ObjectPtr at(const std::string& key) const override { return values.at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override { return values.at(index); }

            void replace(const std::string& key, ObjectPtr o) override { replace(std::stoul(key), std::move(o)); }
            void replace(std::size_t index, ObjectPtr o) override { this->values[index] = o; }

            iterator begin() override { return iterator(values.begin()); }
            iterator end() override { return iterator(values.end()); }
            const_iterator begin() const override { return const_iterator(values.cbegin()); }
            const_iterator end() const override { return const_iterator(values.cend()); }

            void push(ObjectPtr other) override { values.push_back(other); };
            ObjectPtr pop() override { auto val = values.back(); values.pop_back(); return val; };

            void clear() override { values.clear(); }
            void reserve(std::size_t reserve) override { values.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override { return values; }
            void set_values(std::vector<ObjectPtr> new_values) override { values = std::move(new_values); }

            // ====== OBJECT METHOD =======

            ObjectPtr copy() const override { return std::make_shared<Vector>(values, negative); }

            bool equal(const ObjectPtr other) const override;

            void add(const ObjectPtr other) override;
            void sub(const ObjectPtr other) override;

            std::size_t size() const override { return values.size(); }

            std::string to_string() const override;
            std::size_t hash() const override {
                std::size_t seed = 0UL;
                for(const auto& obj: values) {
                    seed ^= obj->hash() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
                return seed;
            }
    };

    class Bag: public Cluster {
        private:
            std::vector<ObjectPtr> values;
        public:
            Bag()
                : Cluster(Class::cluster_bag) {}
            Bag(bool negative)
                : Cluster(Class::cluster_bag, negative) {}
            Bag(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_bag, negative), values(std::move(values)) {}
            ~Bag() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<Bag>();
                tmp->reserve(reserve);

                return tmp;
            }
            std::shared_ptr<Cluster> make_new(std::vector<ObjectPtr> values) const override {
                return std::make_shared<Bag>(std::move(values));
            }

            ObjectPtr at(const std::string& key) const override { return at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override;

            void replace(const std::string& key, ObjectPtr o) override { replace(std::stoul(key), std::move(o)); }
            void replace(std::size_t index, ObjectPtr o) override;

            iterator begin() override { return iterator(values.begin()); }
            iterator end() override { return iterator(values.end()); }
            const_iterator begin() const override { return const_iterator(values.cbegin()); }
            const_iterator end() const override { return const_iterator(values.cend()); }

            void push(ObjectPtr other) override { values.push_back(other); };
            ObjectPtr pop() override;

            void clear() override { values.clear(); }
            void reserve(std::size_t reserve) override { values.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override;
            void set_values(std::vector<ObjectPtr> new_values) override { values = new_values; }

            // ====== OBJECT METHOD =======

            ObjectPtr copy() const override { return std::make_shared<Bag>(values, negative); }

            bool equal(const ObjectPtr other) const override;

            void add(const ObjectPtr other) override;
            void sub(const ObjectPtr other) override;

            std::string to_string() const override;
            
            std::size_t size() const override { return values.size(); }
            std::size_t hash() const override {
                std::size_t seed = 0UL;
                for(const auto& obj: values) {
                    seed ^= obj->hash() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
                return seed;
            }
    };

    inline std::shared_ptr<Cluster> to_cluster(ObjectPtr o) {
        if(!o)
            throw std::invalid_argument("None value");
        if(!o->inherence(Class::cluster))
            throw std::invalid_argument("Must a cluster inherence");
        
        return std::static_pointer_cast<Cluster>(o);
    }

    inline std::int64_t get_integer(const ObjectPtr& o) {
        if(!o) throw std::invalid_argument("None value");
        if(!o->get_class()->inherence(Class::cluster)) throw std::invalid_argument("You must inhrence cluster");
        auto* cluster = static_cast<Cluster*>(o.get()); 
        if(
            !cluster->one_terminal() && (cluster->at(0)->inherence(Class::terminal_number))
        ) throw std::invalid_argument("You must have only one number");
        
        if(cluster->at(0)->get_class() == Class::terminal_integer) {
            return get<std::int64_t>(static_cast<Terminal*>(cluster->at(0).get())->get_value());
        } else if(cluster->at(0)->get_class() == Class::terminal_float) {
            return static_cast<std::int64_t>(get<double>(static_cast<Terminal*>(cluster->at(0).get())->get_value()));
        }

        throw std::invalid_argument("Unsupport formatage number of `" + cluster->at(0)->get_class()->get_name()  + "` to integer");
    }

    inline double get_float(const ObjectPtr& o) {
        if(!o) throw std::invalid_argument("None value");
        if(!o->get_class()->inherence(Class::cluster)) throw std::invalid_argument("You must inhrence cluster");
        auto* cluster = static_cast<Cluster*>(o.get()); 
        if(
            !cluster->one_terminal() && (cluster->at(0)->inherence(Class::terminal_number))
        ) throw std::invalid_argument("You must have only one number");
        
        if(cluster->at(0)->get_class() == Class::terminal_integer) {
            return static_cast<double>(get<std::int64_t>(static_cast<Terminal*>(cluster->at(0).get())->get_value()));
        } else if(cluster->at(0)->get_class() == Class::terminal_float) {
            return get<double>(static_cast<Terminal*>(cluster->at(0).get())->get_value());
        }

        throw std::invalid_argument("Unsupport formatage number of `" + cluster->at(0)->get_class()->get_name()  + "` to integer");
    }
}

#endif /* HOIHOI_CLUSTER_HPP */
