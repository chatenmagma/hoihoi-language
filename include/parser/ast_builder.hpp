#ifndef HOIHOI_AST_BUILDER_HPP
#define HOIHOI_AST_BUILDER_HPP

#include "HoihoiParser.h"

#include "ast/ast.hpp"

namespace hoihoi {
    class AstBuilder {
        public:
            AstBuilder() = default;
            ~AstBuilder() = default;
            
            static program build(const std::string& code);

        private:
            static SourceLocation get_source(antlr4::Token* token) {
                return SourceLocation(
                    token->getLine(),
                    token->getCharPositionInLine()
                );
            }

            static program build_program(HoihoiParser::ProgramContext* context);

            static std::unique_ptr<Statement> build_statement(HoihoiParser::StmtContext* context);
            static std::unique_ptr<AssignementStatement> build_assignement_statement(HoihoiParser::AssignContext* context);
            static std::unique_ptr<ExpressionStatement> build_expression_statement(HoihoiParser::ExprContext* context);
            static std::unique_ptr<FunctionDeclaration> build_function_declaration_statement(HoihoiParser::FunStmtContext* context);

            static std::unique_ptr<IfStatement> build_if_statement(HoihoiParser::IfStmtContext* context);
            static std::unique_ptr<IfStatement> build_elif(HoihoiParser::IfStmtContext* ctx, std::vector<std::unique_ptr<Statement>> end_else, size_t index);
            static std::unique_ptr<WhileStatement> build_while_statement(HoihoiParser::WhileStmtContext* ctx);

            static std::unique_ptr<Expression> build_expression(HoihoiParser::ExprContext* context);
            static std::unique_ptr<Function> build_function(HoihoiParser::FunContext* context);

            static std::unique_ptr<Expression> build_attribute(HoihoiParser::AttributeContext* context);

            static std::unique_ptr<Expression> build_compaission(HoihoiParser::ComparaisionContext* context);
            static std::unique_ptr<Expression> build_or(HoihoiParser::OrContext* context);
            static std::unique_ptr<Expression> build_and(HoihoiParser::AndContext* context);

            static std::unique_ptr<Expression> build_addition(HoihoiParser::AdditionContext* context);
            static std::unique_ptr<Expression> build_multiplication(HoihoiParser::MultiplicationContext* context);

            static std::unique_ptr<Expression> build_primary(HoihoiParser::PrimaryContext* context);

            static InstancePrimitive build_primitive(HoihoiParser::PrimitiveContext* context);

            static std::unique_ptr<ClusterLiteral> build_cluster_literal(HoihoiParser::ClusterLiteralContext * context);
    };
}

#endif /* HOIHOI_AST_BUILDER_HPP */
