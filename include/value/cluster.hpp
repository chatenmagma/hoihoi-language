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

            virtual std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const = 0;

            virtual ObjectPtr at(const std::string& key) const = 0;
            virtual ObjectPtr at(std::size_t index) const = 0;

            virtual void push(ObjectPtr other) = 0;
            virtual ObjectPtr pop() = 0;

            virtual void reserve(std::size_t reserve) = 0;

            virtual std::vector<ObjectPtr> get_values() const = 0;
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

            void reserve(std::size_t reserve) override { value.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override;

            // ====== OBJECT METHOD ======

            ObjectPtr copy() const override { return std::make_shared<String>(std::move(value), negative); }
            void assign(const ObjectPtr) override;

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

    class ClusterOrdered: public Cluster {
        private:
            std::vector<ObjectPtr> values;
        public:
            ClusterOrdered()
                : Cluster(Class::cluster_ordered) {}
            ClusterOrdered(bool negative)
                : Cluster(Class::cluster_ordered, negative) {}
            ClusterOrdered(std::vector<ObjectPtr> values, bool negative = false)
                : Cluster(Class::cluster_ordered, negative), values(std::move(values)) {}
            ~ClusterOrdered() override = default;

            // ====== CLUSTER METHOD =====

            std::shared_ptr<Cluster> make_empty(std::size_t reserve = 0UL) const override {
                auto tmp = std::make_shared<ClusterOrdered>();
                tmp->reserve(reserve);

                return tmp;
            }

            ObjectPtr at(const std::string& key) const override { return values.at(std::stoul(key)); }
            ObjectPtr at(std::size_t index) const override { return values.at(index); }

            void push(ObjectPtr other) override { values.push_back(other); };
            ObjectPtr pop() override { auto val = values.back(); values.pop_back(); return val; };

            void reserve(std::size_t reserve) override { values.reserve(reserve); }

            std::vector<ObjectPtr> get_values() const override { return values; }

            // ====== OBJECT METHOD =======

            ObjectPtr copy() const override { return std::make_shared<ClusterOrdered>(values, negative); }
            void assign(const ObjectPtr) override;

            bool equal(const ObjectPtr other) const override;

            void add(const ObjectPtr other) override;
            void sub(const ObjectPtr other) override;
            void mul(const ObjectPtr other) override;
            void div(const ObjectPtr other) override;

            std::size_t size() const override { return values.size(); }
    };
}

#endif /* HOIHOI_CLUSTER_HPP */
