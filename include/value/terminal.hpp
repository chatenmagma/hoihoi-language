#ifndef HOIHOI_TERMINAL_HPP
#define HOIHOI_TERMINAL_HPP

#include <variant>
#include <functional>
#include <vector>
#include <cmath>

#include "object.hpp"
#include "vm/bytecode.hpp"
#include "thing.h"

namespace hoihoi {
    struct Module;
    using Builtin = std::function<ObjectPtr(std::vector<ObjectPtr>)>;

    using TerninalValue = std::variant<
        TernaryLogical,
        char,
        std::int64_t,
        double,
        Thing,
        std::shared_ptr<Builtin>,
        std::shared_ptr<Bytecode>,
        std::shared_ptr<Module>
    >;

    /**
     * \brief Make a terminal cluster of ternary value. The language do that all primitive low, neutral and high are the same static pointer.
     * \return the terminal from the value
     */
    ObjectPtr make_logical(TernaryLogical log) noexcept;

    class Terminal final: public Object {
        private:
            TerninalValue value;
        public:
            Terminal(std::shared_ptr<Class> klass, TerninalValue value)
                : Object(klass), value(value) {}
            Terminal(std::shared_ptr<Class> klass, TerninalValue value, bool negative)
                : Object(klass, negative), value(value) {}
            ~Terminal() override = default;

            const static ObjectPtr positive_thing;
            const static ObjectPtr negative_thing;

            const static ObjectPtr high;
            const static ObjectPtr neutral;
            const static ObjectPtr low;

            ObjectPtr copy() const override {
                return std::make_shared<Terminal>(get_class(), value, negative);
            }

            bool equal(const ObjectPtr other) const override {
                if(this == other.get()) return true;

                auto* terminal = dynamic_cast<Terminal*>(other.get());
                if(!terminal || (terminal->value.index() != value.index())) return false;

                if(std::holds_alternative<Thing>(value))
                    return true;
                else if(std::holds_alternative<TernaryLogical>(value)) 
                    return get<TernaryLogical>(value) == get<TernaryLogical>(terminal->value);
                else if(std::holds_alternative<char>(value)) 
                    return get<char>(value) == get<char>(terminal->value);
                else if(std::holds_alternative<std::int64_t>(value))
                    return get<std::int64_t>(value) == get<std::int64_t>(terminal->value);
                else if(std::holds_alternative<double>(value))
                    return get<double>(value) == get<double>(terminal->value);
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

                return make_logical(std::max(
                    get<TernaryLogical>(value), 
                    get<TernaryLogical>(terminal->value)
                ));
            }

            ObjectPtr and_operation(const ObjectPtr other) const override {
                auto* terminal = dynamic_cast<Terminal*>(other.get());

                if(!terminal || (terminal->get_value().index() != value.index()) || !std::holds_alternative<TernaryLogical>(value)) 
                    throw std::invalid_argument(format(
                        "You cannot or with a `{}` into `{}`",
                        this->get_class()->get_name(),
                        other->get_class()->get_name()
                    ));
                    
                return make_logical(std::min(
                    get<TernaryLogical>(value), 
                    get<TernaryLogical>(terminal->value)
                ));
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
                    else if constexpr(std::is_same_v<T, std::int64_t>) return std::to_string(val);
                    else if constexpr(std::is_same_v<T, double>) return std::to_string(val);
                    else if constexpr(std::is_same_v<T, Thing>) return hoihoi::to_string(val);
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

            std::size_t hash() const override {
                return std::visit([](auto&& val) -> std::size_t {
                    using T = std::decay_t<decltype(val)>;

                    if constexpr(std::is_same_v<T, TernaryLogical>) return std::hash<std::uint8_t>{}((std::uint8_t) val);
                    else if constexpr(std::is_same_v<T, char>) return std::hash<char>{}(val);
                    else if constexpr(std::is_same_v<T, std::int64_t>) return std::hash<std::int64_t>{}(val);
                    else if constexpr(std::is_same_v<T, double>) return std::hash<double>{}(val);
                    else if constexpr(std::is_same_v<T, Thing>) return 0UL;
                    else
                        return std::hash<std::intptr_t>{}((std::intptr_t) val.get());
                }, value);
            }
    };

    constexpr ObjectPtr make_character(char value, bool negative = false) {
        return std::make_shared<Terminal>(Class::terminal_character, value, negative);
    }

    constexpr ObjectPtr make_float(double value, bool negative = false) {
        return std::make_shared<Terminal>(Class::terminal_float, value, negative);
    }

    constexpr ObjectPtr make_integer(std::int64_t value, bool negative = false) {
        return std::make_shared<Terminal>(Class::terminal_integer, value, negative);
    }

    constexpr ObjectPtr make_integer(std::shared_ptr<Builtin> value, bool negative = false) {
        return std::make_shared<Terminal>(Class::terminal_builtin, value, negative);
    }

    constexpr ObjectPtr make_module(std::shared_ptr<Module> value) {
        return std::make_shared<Terminal>(Class::terminal_module, value, false);
    }

    constexpr ObjectPtr make_builtin(Builtin builtin) {
        return std::make_shared<Terminal>(
            Class::terminal_builtin, 
            std::make_shared<Builtin>(std::move(builtin)),
            false
        );
    }

    /**
     * \brief Make a terminal cluster of thing value. The language do that all primitive thing are the same static pointer.
     * \return the terminal from the value
     */
    constexpr ObjectPtr make_thing(bool negative = false) {
        return (negative)? Terminal::negative_thing: Terminal::positive_thing;
    }

    inline void addition(ObjectPtr& numA, const ObjectPtr& numB) {
        if(!numA->inherence(Class::terminal_number) || !numB->inherence(Class::terminal_number))
            throw std::invalid_argument("You must have only numbers");

        bool is_int = true;
        std::int64_t val_int64 = 0L;
        double val_double = 0.0;

        if(numB->get_class() == Class::terminal_integer)
            val_int64 = get<std::int64_t>(static_cast<Terminal*>(numB.get())->get_value());
        else if(numB->get_class() == Class::terminal_float) {
            val_double = get<double>(static_cast<Terminal*>(numB.get())->get_value());
            is_int = (val_double == std::floor(val_double));
        }

        if(numA->get_class() == Class::terminal_integer) {
            if(is_int) {
                static_cast<Terminal*>(numA.get())->set_value(
                    get<std::int64_t>(static_cast<Terminal*>(numA.get())->get_value()) +
                    val_int64 + static_cast<std::int64_t>(val_double)
                );
            } else {
                static_cast<Terminal*>(numA.get())->set_value(
                    static_cast<double>(
                        get<std::int64_t>(static_cast<Terminal*>(numA.get())->get_value())
                    ) -
                    static_cast<double>(val_int64) + val_double
                );
            }
        } else if(numA->get_class() == Class::terminal_float) {
            static_cast<Terminal*>(numA.get())->set_value(
                get<double>(static_cast<Terminal*>(numA.get())->get_value()) +
                val_double + static_cast<double>(val_int64)
            );

        } else {
            throw std::runtime_error("Unknown number type");
        }
    }

    inline void substract(ObjectPtr& numA, const ObjectPtr& numB) {
        if(!numA->inherence(Class::terminal_number) || !numB->inherence(Class::terminal_number))
            throw std::invalid_argument("You must have only numbers");

        bool is_int = true;
        std::int64_t val_int64 = 0L;
        double val_double = 0.0;

        if(numB->get_class() == Class::terminal_integer)
            val_int64 = get<std::int64_t>(static_cast<Terminal*>(numB.get())->get_value());
        else if(numB->get_class() == Class::terminal_float) {
            val_double = get<double>(static_cast<Terminal*>(numB.get())->get_value());
            is_int = (val_double == std::floor(val_double));
        }

        if(numA->get_class() == Class::terminal_integer) {
            if(is_int) {
                static_cast<Terminal*>(numA.get())->set_value(
                    get<std::int64_t>(static_cast<Terminal*>(numA.get())->get_value()) -
                    val_int64 + static_cast<std::int64_t>(val_double)
                );
            } else {
                static_cast<Terminal*>(numA.get())->set_value(
                    static_cast<double>(
                        get<std::int64_t>(static_cast<Terminal*>(numA.get())->get_value())
                    ) -
                    static_cast<double>(val_int64) + val_double
                );
            }
        } else if(numA->get_class() == Class::terminal_float) {
            static_cast<Terminal*>(numA.get())->set_value(
                get<double>(static_cast<Terminal*>(numA.get())->get_value()) -
                val_double + static_cast<double>(val_int64)
            );

        } else {
            throw std::runtime_error("Unknown number type");
        }
    }
}

#endif /* HOIHOI_TERMINAL_HPP */
