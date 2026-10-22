#ifndef HOIHOI_TERMINAL_HPP
#define HOIHOI_TERMINAL_HPP

#include <variant>
#include <functional>
#include <vector>

#include "object.hpp"
#include "vm/bytecode.hpp"

namespace hoihoi {
    using Builtin = std::function<ObjectPtr(std::vector<ObjectPtr>)>;

    using TerninalValue = std::variant<
        TernaryLogical,
        char,
        std::shared_ptr<Builtin>,
        std::shared_ptr<Bytecode>
    >;

    class Terminal final: public Object {
        private:
            TerninalValue value;
        public:
            Terminal(std::shared_ptr<Class> klass, TerninalValue value)
                : Object(klass), value(value) {}
            Terminal(std::shared_ptr<Class> klass, TerninalValue value, bool negative)
                : Object(klass, negative), value(value) {}
            ~Terminal() override = default;

            ObjectPtr copy() const override {
                return std::make_shared<Terminal>(get_class(), value, negative);
            }

            void assign(const ObjectPtr other) override {
                auto* terminal = dynamic_cast<Terminal*>(other.get());

                if(!terminal || terminal->get_value().index() != value.index()) {
                    throw std::invalid_argument(format(
                        "You cannot assign with a `{}` into `{}`",
                        this->get_class()->get_name(),
                        other->get_class()->get_name()
                    ));
                }

                value = terminal->value;
                negative = terminal->negative;
            }

            bool equal(const ObjectPtr other) const override {
                if(this == other.get()) return true;

                auto* terminal = dynamic_cast<Terminal*>(other.get());
                if(!terminal || (terminal->value.index() != value.index())) return false;

                if(std::holds_alternative<TernaryLogical>(value)) 
                    return get<TernaryLogical>(value) == get<TernaryLogical>(terminal->value);
                else if(std::holds_alternative<char>(value)) 
                    return get<char>(value) == get<char>(terminal->value);
                else
                    return false;
            }

            ObjectPtr or_operation(const ObjectPtr other) const override {
                auto* terminal = dynamic_cast<Terminal*>(other.get());

                if(!terminal || (terminal->get_value().index() != value.index()) || !std::holds_alternative<TernaryLogical>(value)) 
                    throw std::invalid_argument(format(
                        "You cannot or with a `{}` into `{}`",
                        this->get_class()->get_name(),
                        other->get_class()->get_name()
                    ));

                return std::make_shared<Terminal>(
                    Class::terminal_logical, std::max(get<TernaryLogical>(value), 
                    get<TernaryLogical>(terminal->value))
                );
            }

            ObjectPtr and_operation(const ObjectPtr other) const override {
                auto* terminal = dynamic_cast<Terminal*>(other.get());

                if(!terminal || (terminal->get_value().index() != value.index()) || !std::holds_alternative<TernaryLogical>(value)) 
                    throw std::invalid_argument(format(
                        "You cannot or with a `{}` into `{}`",
                        this->get_class()->get_name(),
                        other->get_class()->get_name()
                    ));
                    
                return std::make_shared<Terminal>(
                    Class::terminal_logical, std::min(get<TernaryLogical>(value), 
                    get<TernaryLogical>(terminal->value))
                );
            }

            void add(const ObjectPtr other) override {
                throw std::invalid_argument(format(
                    "You cannot add with a `{}` into `{}`",
                    this->get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            void sub(const ObjectPtr other) override {
                throw std::invalid_argument(format(
                    "You cannot sub with a `{}` into `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            void mul(const ObjectPtr other) override {
                throw std::invalid_argument(format(
                    "You cannot mul with a `{}` into `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            void div(const ObjectPtr other) override {
                throw std::invalid_argument(format(
                    "You cannot div with a `{}` into `{}`",
                    get_class()->get_name(),
                    other->get_class()->get_name()
                ));
            }

            std::string to_string() const override {
                return std::visit([&](auto&& val) -> std::string {
                    using T = std::decay_t<decltype(val)>;

                    if constexpr(std::is_same_v<T, TernaryLogical>) return hoihoi::to_string(val);
                    else if constexpr(std::is_same_v<T, char>) return std::string(1, val);
                    else
                        return std::format(
                            "<{} {} {:x}>", 
                            hoihoi::to_string(get_logical()),
                            this->get_class()->get_name(),
                            (std::intptr_t) this
                        );
                }, value);
            }

            const TerninalValue& get_value() const { return value; }
            void set_value(TerninalValue value) { this->value = value; } 
    };
}

#endif /* HOIHOI_TERMINAL_HPP */
