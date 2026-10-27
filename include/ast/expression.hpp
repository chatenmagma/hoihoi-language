#ifndef HOIHOI_EXPRESSION
#define HOIHOI_EXPRESSION

#include <cstdint>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <unordered_map>
#include <value/value.hpp>

#include "vm/source_location.hpp"

namespace hoihoi {
    struct SourceMapEntry {
        std::size_t instruction_offset;
        std::unordered_map<std::size_t, SourceLocation> location;
    };

    struct Expression {
        SourceLocation location;

        Expression(SourceLocation location)
            : location(location) {}
        virtual ~Expression() = default;
    };

    struct Variable final: public Expression {
        std::string name;
        
        Variable(SourceLocation location, const std::string& name)
            : Expression(location), name(name){}
        ~Variable() override = default;
    };

    struct Function final: public Expression {
        std::string name;
        std::vector<std::unique_ptr<Expression>> args;

        Function(SourceLocation location, const std::string& name, std::vector<std::unique_ptr<Expression>> args)
            : Expression(location), name(name), args(std::move(args)) {}
        ~Function() override = default;
    };

    enum class KindAttribute: std::uint8_t {
        GET,
        CALL,
        SELF_CALL
    };

    struct Attribute final: public Expression {
        std::unique_ptr<Expression> value;
        std::unique_ptr<Expression> name;
        KindAttribute kind;
        std::vector<std::unique_ptr<Expression>> args;


        Attribute(SourceLocation location, std::unique_ptr<Expression> value, std::unique_ptr<Expression> name, KindAttribute kind, std::vector<std::unique_ptr<Expression>> args)
            : Expression(location), value(std::move(value)), name(std::move(name)), kind(kind), args(std::move(args)) {}
        ~Attribute() = default;  
    };

    using InstancePrimitive = std::variant<std::string, std::int64_t, double, TernaryLogical, std::nullptr_t>;

    struct Primitive final: public Expression {
        InstancePrimitive value;
        bool negative;

        Primitive(SourceLocation location, InstancePrimitive value, bool negative = false)
            : Expression(location), value(value), negative(negative) {}
        ~Primitive() override = default;
    };

    enum class KindCluster: std::uint8_t {
        VECTOR,
        TUPLE,
        SET,
        BAG,
    };

    struct ClusterLiteral final: public Expression {
        std::vector<std::unique_ptr<Expression>> values;
        KindCluster kind;
        bool negative;

        ClusterLiteral(SourceLocation location, std::vector<std::unique_ptr<Expression>> values, KindCluster kind = KindCluster::VECTOR, bool negative = false)
            : Expression(location), values(std::move(values)), kind(kind), negative(negative) {}
        ~ClusterLiteral() override = default;
    };

    enum class UnaryOperator: std::uint8_t {
        NOT
    };

    struct UnaryExpression final: public Expression {
        UnaryOperator op;

        std::unique_ptr<Expression> value;

        UnaryExpression(SourceLocation location, UnaryOperator op, std::unique_ptr<Expression> value)
            : Expression(location), op(op), value(std::move(value)) {}
        ~UnaryExpression() override = default;
    };

    struct BinaryExpression final: public Expression {
        BinaryOperator op;

        std::unique_ptr<Expression> left;
        std::unique_ptr<Expression> right;

        BinaryExpression(SourceLocation location, BinaryOperator op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
            : Expression(location), op(op), left(std::move(left)), right(std::move(right)) {}
        ~BinaryExpression() override = default;
    };
}

#endif /* HOIHOI_EXPRESSION */
