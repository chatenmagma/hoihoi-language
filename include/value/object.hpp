#ifndef HOIHOI_OBJECT_HPP
#define HOIHOI_OBJECT_HPP

#include <format>
#include <memory>
#include <unordered_map>

#include "ternary_logical.hpp"

namespace hoihoi {
    class Class;
    class Object;

    using ObjectPtr = std::shared_ptr<Object>;

    class Class {
        private:
            std::unordered_map<std::string, ObjectPtr> attributes;
            Class* parent;
        public:
            Class(const std::string& class_name, std::shared_ptr<Class> parent = nullptr);
            ~Class() = default;

            static std::shared_ptr<Class> cluster;
                static std::shared_ptr<Class> cluster_thing;
                static std::shared_ptr<Class> cluster_bag;
                    static std::shared_ptr<Class> cluster_set;
                static std::shared_ptr<Class> cluster_vector;
                    static std::shared_ptr<Class> cluster_string;
                    static std::shared_ptr<Class> cluster_tuple;


            static std::shared_ptr<Class> terminal;
                static std::shared_ptr<Class> terminal_number;
                    static std::shared_ptr<Class> terminal_integer;
                    static std::shared_ptr<Class> terminal_float;
                static std::shared_ptr<Class> terminal_logical;
                static std::shared_ptr<Class> terminal_character;
                static std::shared_ptr<Class> terminal_builtin;
                static std::shared_ptr<Class> terminal_funtion;
                static std::shared_ptr<Class> terminal_thing;

            std::string get_name() const;

            ObjectPtr get_attribute(const std::string& name) const {
                auto it = attributes.find(name);
                if(it != attributes.end()) return it->second;
                if(parent) return parent->get_attribute(name);

                throw std::invalid_argument("The class do not have the attribute `" + name + "`");
            }

            inline void set_attribute(const std::string& name, ObjectPtr object) { attributes.insert_or_assign(name, object); }
            inline Class& get_parent() const noexcept { return *parent; }

            bool inherence(const Class* target) const noexcept {
                if(target == this) return true;

                Class* current_parent = parent;
                while(current_parent) {
                    if(current_parent == target) return true;
                    
                    current_parent = current_parent->parent;
                }

                return false;
            }

            inline bool inherence(const std::shared_ptr<Class> target) const {
                return inherence(target.get());
            }

            inline std::string to_string() const { return std::format("<class {}>", get_name()); }
    };

    class Object {
        private:
            std::shared_ptr<Class> klass;
        protected:     
            bool negative;
        public:
            Object(std::shared_ptr<Class> klass)
                : klass(klass) {}
            Object(std::shared_ptr<Class> klass, bool negative)
                : klass(klass), negative(negative) {}
            virtual ~Object() = default;

            virtual ObjectPtr copy() const = 0;

            virtual bool equal(const ObjectPtr other) const { return this == other.get(); }

            virtual ObjectPtr or_operation(const ObjectPtr other) const = 0;
            virtual ObjectPtr and_operation(const ObjectPtr other) const = 0;
            virtual ObjectPtr lower_operation(const ObjectPtr other) const;
            virtual ObjectPtr greater_operation(const ObjectPtr other) const;

            virtual void add(const ObjectPtr other) = 0;
            virtual void sub(const ObjectPtr other) = 0;
            virtual void mul(const ObjectPtr other) = 0;
            virtual void div(const ObjectPtr other) = 0;

            virtual std::string to_string() const { 
                return std::format(
                    "<{} {} {:x}>", 
                    hoihoi::to_string(get_logical()),
                    klass->get_name(), 
                    (std::intptr_t) this
                ); 
            }

            virtual std::size_t size() const { return 1UL; }

            inline void opposite() noexcept { negative = !negative; }

            inline bool is_low() const { return negative & !is_neutral(); }
            inline bool is_neutral() const { return size() == 0UL; }
            inline bool is_high() const { return !negative & !is_neutral(); }

            inline TernaryLogical get_logical() const {
                return is_neutral()? TernaryLogical::NEUTRAL:
                       is_high()? TernaryLogical::HIGH: TernaryLogical::LOW;
            }

            inline bool is_negative() const noexcept { return negative; }

            inline std::shared_ptr<Class> get_class() const noexcept { return klass; }
    };
}

#endif /* HOIHOI_OBJECT_HPP */
