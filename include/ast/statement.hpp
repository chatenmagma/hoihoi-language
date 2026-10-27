#ifndef HOIHOI_STATEMENT_HPP
#define HOIHOI_STATEMENT_HPP

#include <memory>
#include <vector>

#include "expression.hpp"

namespace hoihoi {
    using hoihoi_number = double;
    using hoihoi_string = std::string;

    struct Statement {
        virtual ~Statement() = default;
    };

    struct IfStatement final: public Statement {
        std::unique_ptr<Expression> condition;

        std::vector<std::unique_ptr<Statement>> body;
        std::vector<std::unique_ptr<Statement>> body_else;

        IfStatement(std::unique_ptr<Expression> condition, std::vector<std::unique_ptr<Statement>> body)
            : condition(std::move(condition)), body(std::move(body)) {}
        
        IfStatement(
            std::unique_ptr<Expression> condition, 

            std::vector<std::unique_ptr<Statement>> body,
            std::vector<std::unique_ptr<Statement>> body_else
        )
            :
                condition(std::move(condition)),

                body(std::move(body)),
                body_else(std::move(body_else))
        {}
        ~IfStatement() override = default;
    };

    struct WhileStatement final: public Statement {
        std::unique_ptr<Expression> condition;

        std::vector<std::unique_ptr<Statement>> body;

        WhileStatement(std::unique_ptr<Expression> condition, std::vector<std::unique_ptr<Statement>> body)
            : condition(std::move(condition)), body(std::move(body)) {}
        ~WhileStatement() override = default;
    };

    struct AssignementStatement: public Statement {
        std::string name;
        std::unique_ptr<Expression> expression;

        AssignementStatement(const std::string& name, std::unique_ptr<Expression> expression)
            : name(name), expression(std::move(expression)) {}
        virtual ~AssignementStatement() override = default;
    };

    struct AssignementOperationStatement final: public AssignementStatement {
        BinaryOperator op;

        AssignementOperationStatement(const std::string& name, std::unique_ptr<Expression> expression, BinaryOperator operation)
            : AssignementStatement(name, std::move(expression)), op(operation) {}
        ~AssignementOperationStatement() override = default;
    };

    struct ExpressionStatement final: public Statement {
        std::unique_ptr<Expression> expression;

        ExpressionStatement(std::unique_ptr<Expression> expression)
            : expression(std::move(expression)) {}
        ~ExpressionStatement() override = default;
    };

    struct PassStatement final: public Statement {
        PassStatement() = default;
        ~PassStatement() override = default;
    };

    struct ReturnStatement final: public Statement {
        std::unique_ptr<Expression> expression;

        ReturnStatement(): expression(nullptr) {}
        ReturnStatement(std::unique_ptr<Expression> expression)
            : expression(std::move(expression)) {}
        ~ReturnStatement() override = default;  
    };

    struct FunctionDeclaration final: public Statement {
        std::string name;
        std::vector<std::string> args;
        std::vector<std::unique_ptr<Statement>> body;

        FunctionDeclaration(const std::string& name, std::vector<std::string> args, std::vector<std::unique_ptr<Statement>> body)
            : name(name), args(std::move(args)), body(std::move(body)) {}
        ~FunctionDeclaration() override = default;
    };
}

#endif /* HOIHOI_STATEMENT_HPP */
