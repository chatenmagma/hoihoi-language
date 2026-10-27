#ifndef HOIHOI_CLUSTER_HPP
#define HOIHOI_CLUSTER_HPP

#include <vector>

#include "object.hpp"

namespace hoihoi {
    class Cluster: public Object {
        public:
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

            virtual ObjectPtr at(const std::string& key) const = 0;
            virtual ObjectPtr at(std::size_t index) const = 0;

            virtual void clear() = 0;

            virtual void push(ObjectPtr other) = 0;
            virtual ObjectPtr pop() = 0;

            virtual void reserve(std::size_t reserve) = 0;

            virtual std::vector<ObjectPtr> get_values() const = 0;
            virtual void set_values(std::vector<ObjectPtr> n_values) = 0;
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

            ObjectPtr at(const std::string& key) const override { return at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override;

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
                else if(get_logical() == TernaryLogical::LOW && other->get_logical() == TernaryLogical::LOW) opposite();
            }

            void div(const ObjectPtr other) override {
                if(other->size() == 0UL) throw std::invalid_argument("You cannot divide by zero");

                values /= other->size();

                if(get_logical() != other->get_logical()) opposite();
                else if(get_logical() == TernaryLogical::LOW && other->get_logical() == TernaryLogical::LOW) opposite();
            }

            std::size_t size() const override { return values; }
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

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<Tuple>();
                tmp->reserve(reserve);

                return tmp;
            }

            ObjectPtr at(const std::string& key) const override { return values.at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override { return values.at(index); }

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

            ObjectPtr at(const std::string& key) const override { return at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override;

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
    };

    class Vector: public Cluster {
        private:
            std::vector<ObjectPtr> values;
        public:
            Vector()
                : Cluster(Class::cluster_vector) {}
            Vector(bool negative)
                : Cluster(Class::cluster_vector, negative) {}
            Vector(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_vector, negative), values(std::move(values)) {}
            ~Vector() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<Vector>();
                tmp->reserve(reserve);

                return tmp;
            }

            ObjectPtr at(const std::string& key) const override { return values.at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override { return values.at(index); }

            void push(ObjectPtr other) override { values.push_back(other); };
            ObjectPtr pop() override { auto val = values.back(); values.pop_back(); return val; };

            void clear() override { values.clear(); }
            void reserve(std::size_t reserve) override { values.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override { return values; }
            void set_values(std::vector<ObjectPtr> new_values) override { values = new_values; }

            // ====== OBJECT METHOD =======

            ObjectPtr copy() const override { return std::make_shared<Vector>(values, negative); }

            bool equal(const ObjectPtr other) const override;

            void add(const ObjectPtr other) override;
            void sub(const ObjectPtr other) override;
            void mul(const ObjectPtr other) override;
            void div(const ObjectPtr other) override;

            std::size_t size() const override { return values.size(); }

            std::string to_string() const override;
    };
}

#endif /* HOIHOI_CLUSTER_HPP */
