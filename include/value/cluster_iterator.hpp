#ifndef HOIHOI_CLUSTER_ITERATOR_HPP
#define HOIHOI_CLUSTER_ITERATOR_HPP

#include <memory>
#include <iterator>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <stdexcept>

#include "object.hpp"

namespace hoihoi {

    template<bool IsConst>
    class BasicClusterIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ObjectPtr;
        using difference_type = std::ptrdiff_t;

        using reference = std::conditional_t<
            IsConst,
            const ObjectPtr&,
            ObjectPtr&
        >;

        using pointer = std::conditional_t<
            IsConst,
            const ObjectPtr*,
            ObjectPtr*
        >;

    private:
        struct Interface {
            virtual ~Interface() = default;

            virtual std::unique_ptr<Interface> clone() const = 0;
            virtual reference dereference() const = 0;
            virtual void increment() = 0;
            virtual bool equals(const Interface& other) const = 0;
        };

        template<typename It>
        struct Model final : Interface {
            It current;

            explicit Model(It it)
                : current(std::move(it)) {}

            std::unique_ptr<Interface> clone() const override {
                return std::make_unique<Model>(*this);
            }

            reference dereference() const override {
                if constexpr(IsConst)
                    return *current;
                else {
                    static_assert(
                        !std::is_const_v<
                            std::remove_reference_t<decltype(*current)>
                        >,
                        "This container does not support mutable iteration"
                    );

                    return *current;
                }
            }

            void increment() override {
                ++current;
            }

            bool equals(const Interface& other) const override {
                auto p = dynamic_cast<const Model*>(&other);
                return p && current == p->current;
            }
        };

        struct RepeatedModel final: Interface {
            reference value;
            std::size_t index, count;

            RepeatedModel(reference value, std::size_t index, std::size_t count)
                    : value(value), index(index), count(count) {}
                std::unique_ptr<Interface> clone() const override {
                    return std::make_unique<RepeatedModel>(*this);
                }
                reference dereference() const override { return value; }
                void increment() override { ++index; }
                bool equals(const Interface& other) const override {
                    auto p = dynamic_cast<const RepeatedModel*>(&other);

                    return p
                        && value == p->value
                        && index == p->index
                        && count == p->count;
                }
            };

            struct CharacterModel final: Interface {
                std::string::const_iterator current;
                std::string::const_iterator last;

                CharacterModel(std::string::const_iterator current, std::string::const_iterator last)
                    : current(current), last(last) {}
                std::unique_ptr<Interface> clone() const override {
                    return std::make_unique<CharacterModel>(*this); 
                }

                reference dereference() const override {
                    throw std::logic_error("CharacterModel: implementation required");
                }

                void increment() override { ++current; }
                bool equals(const Interface& other) const override {
                    auto p = dynamic_cast<const CharacterModel*>(&other);
                    return p && current == p->current && last == p->last;
                }
            };

        std::unique_ptr<Interface> impl;

    public:
        BasicClusterIterator() = default;

        template<typename It>
        explicit BasicClusterIterator(It it)
            : impl(std::make_unique<Model<It>>(std::move(it))) {}

        BasicClusterIterator(const BasicClusterIterator& other)
            : impl(other.impl ? other.impl->clone() : nullptr) {}

        BasicClusterIterator(BasicClusterIterator&&) noexcept = default;

        static BasicClusterIterator repeated(reference value, std::size_t current, std::size_t last) {
            BasicClusterIterator res;
            res.impl = std::make_unique<RepeatedModel>(value, current, last);
            return res;
        }

        static BasicClusterIterator character(std::string::const_iterator current, std::string::const_iterator last) {
            BasicClusterIterator res;
            res.impl = std::make_unique<CharacterModel>(current, last);
            return res;
        }

        BasicClusterIterator& operator=(
            const BasicClusterIterator& other
        ) {
            if (this != &other)
                impl = other.impl ? other.impl->clone() : nullptr;

            return *this;
        }

        BasicClusterIterator& operator=(
            BasicClusterIterator&&
        ) noexcept = default;

        reference operator*() const {
            if (!impl)
                throw std::logic_error("Invalid ClusterIterator");

            return impl->dereference();
        }

        pointer operator->() const {
            return &(**this);
        }

        BasicClusterIterator& operator++() {
            impl->increment();
            return *this;
        }

        BasicClusterIterator operator++(int) {
            BasicClusterIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        friend bool operator==(
            const BasicClusterIterator& a,
            const BasicClusterIterator& b
        ) {
            if (!a.impl || !b.impl)
                return !a.impl && !b.impl;

            return a.impl->equals(*b.impl);
        }

        friend bool operator!=(
            const BasicClusterIterator& a,
            const BasicClusterIterator& b
        ) {
            return !(a == b);
        }
    };

    using ClusterIterator = BasicClusterIterator<false>;
    using ClusterConstIterator = BasicClusterIterator<true>;

}

#endif
