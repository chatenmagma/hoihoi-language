#include "parser/ast_builder.hpp"

#include <algorithm>

#include "HoihoiLexer.h"

using namespace hoihoi;
using namespace std;

program AstBuilder::build(const string& code) {
    antlr4::ANTLRInputStream input(code);
    HoihoiLexer lexer(&input);

    antlr4::CommonTokenStream tokens(&lexer);
    HoihoiParser parser(&tokens);

    return build_program(parser.program());
}

program AstBuilder::build_program(HoihoiParser::ProgramContext* context) {
    program m_prog;

    for(auto* stmt_ctx: context->stmt())
        m_prog.push_back(move(build_statement(stmt_ctx)));
    
    return m_prog;
}

unique_ptr<Statement> AstBuilder::build_statement(HoihoiParser::StmtContext* ctx) {
    if(auto simple = ctx->simpleStmt()) {
        if(simple->assign())
            return build_assignement_statement(simple->assign());
        else if(simple->expr() && !simple->RETURN())
            return build_expression_statement(simple->expr());
        else if(simple->PASS())
            return make_unique<PassStatement>();
        else if(simple->RETURN()) {
            if(simple->expr())
                return make_unique<ReturnStatement>(build_expression(simple->expr()));
            return make_unique<ReturnStatement>();
        }
    } else if(auto block = ctx->blockStmt()) {
        if(auto ifStmt = block->ifStmt())
            return build_if_statement(ifStmt);
        if(auto whileStmt = block->whileStmt())
            return build_while_statement(whileStmt);
        if(auto funStmt = block->funStmt())
            return build_function_declaration_statement(funStmt);
    } 

    throw runtime_error("Unknow statement");
}

unique_ptr<AssignementStatement> AstBuilder::build_assignement_statement(HoihoiParser::AssignContext* ctx) {
    if(ctx->ADD_ASSIGN()) {
        return make_unique<AssignementOperationStatement>(
            ctx->IDENTIFIER()->getText(),
            build_expression(ctx->expr()),
            BinaryOperator::PLUS
        );
    } else if(ctx->SUB_ASSIGN()) {
        return make_unique<AssignementOperationStatement>(
            ctx->IDENTIFIER()->getText(),
            build_expression(ctx->expr()),
            BinaryOperator::MINUS
        );
    } else if(ctx->MUL_ASSIGN()) {
        return make_unique<AssignementOperationStatement>(
            ctx->IDENTIFIER()->getText(),
            build_expression(ctx->expr()),
            BinaryOperator::MUL
        );
    } else {
        return make_unique<AssignementStatement>(
            ctx->IDENTIFIER()->getText(),
            move(build_expression(ctx->expr()))
        );
    }
}

unique_ptr<FunctionDeclaration> AstBuilder::build_function_declaration_statement(HoihoiParser::FunStmtContext* ctx) {
    string name = ctx->IDENTIFIER()->getText();

    vector<string> args;
    if(ctx->args())
        for(auto* a: ctx->args()->IDENTIFIER())
            args.push_back(a->getText());

    vector<unique_ptr<Statement>> body;
    for(auto* stmt: ctx->suite()->stmt())
        body.push_back(move(build_statement(stmt)));
    
    return make_unique<FunctionDeclaration>(
        name,
        move(args),
        move(body)
    );
}

unique_ptr<ExpressionStatement> AstBuilder::build_expression_statement(HoihoiParser::ExprContext* ctx) {
    return make_unique<ExpressionStatement>(build_expression(ctx));
}

unique_ptr<Expression> AstBuilder::build_expression(HoihoiParser::ExprContext* ctx) {
    if(!ctx) throw runtime_error("build_expression: null ExprContext");

    if(ctx->NOT())
        return make_unique<UnaryExpression>(
            get_source(ctx->NOT()->getSymbol()),
            UnaryOperator::NOT,
            move(build_or(ctx->or_()))
        );

    return build_or(ctx->or_());
}

unique_ptr<IfStatement> AstBuilder::build_elif(HoihoiParser::IfStmtContext* ctx, vector<unique_ptr<Statement>> else_end, size_t index) {
    vector<unique_ptr<Statement>> body;

    for(auto* stmt: ctx->elif(index)->suite()->stmt())
        body.push_back(move(build_statement(stmt)));

    if(index == ctx->elif().size() - 1) {
        return make_unique<IfStatement>(
            move(build_expression(ctx->elif(index)->expr())),

            move(body),
            move(else_end)
        );
    }

    vector<unique_ptr<Statement>> else_body;
    else_body.push_back(
        move(build_elif(ctx, move(else_end), index + 1))
    );

    return make_unique<IfStatement>(
        move(build_expression(ctx->elif(index)->expr())),

        move(body),
        move(else_body)
    );
}

unique_ptr<IfStatement> AstBuilder::build_if_statement(HoihoiParser::IfStmtContext* ctx) {
    vector<unique_ptr<Statement>> body;
    vector<unique_ptr<Statement>> body_else;
    vector<unique_ptr<Statement>> body_elif;

    for(auto* stmt: ctx->suite()->stmt()) {
        body.push_back(move(build_statement(stmt)));
    }

    if(ctx->else_()) {
        for(auto* else_stmt: ctx->else_()->suite()->stmt())
            body_else.push_back(move(build_statement(else_stmt)));
    }

    if(ctx->elif().empty()) {
        return make_unique<IfStatement>(
            move(build_expression(ctx->expr())),

            move(body),
            move(body_else)
        );
    } 

    body_elif.push_back(move(build_elif(ctx, move(body_else), 0UL)));

    return make_unique<IfStatement>(
        move(build_expression(ctx->expr())),

        move(body),
        move(body_elif)
    );
}

unique_ptr<WhileStatement> AstBuilder::build_while_statement(HoihoiParser::WhileStmtContext* ctx) {
    vector<unique_ptr<Statement>> body;

    for(const auto& stmt: ctx->suite()->stmt())
        body.emplace_back(move(build_statement(stmt)));
    
    return make_unique<WhileStatement>(build_expression(ctx->expr()), move(body));
}

unique_ptr<Expression> AstBuilder::build_compaission(HoihoiParser::ComparaisionContext* ctx) {
    if(ctx->addition().empty())
        throw runtime_error("No addition found");
    
    auto left = build_addition(ctx->addition()[0]);
    auto right = build_addition(ctx->addition()[1]);

    if(ctx->EQUAL())
        return make_unique<BinaryExpression>(
            get_source(ctx->EQUAL()->getSymbol()),
            BinaryOperator::EQUAL,
            move(left),
            move(right)
        );

    if(ctx->NOT_EQUAL())
        return make_unique<BinaryExpression>(
            get_source(ctx->NOT_EQUAL()->getSymbol()),
            BinaryOperator::NOT_EQUAL,
            move(left),
            move(right)
        );
    
    if(ctx->LESS_THAN())
        return make_unique<BinaryExpression>(
            get_source(ctx->LESS_THAN()->getSymbol()),
            BinaryOperator::LOWER,
            move(left),
            move(right)
        );
    if(ctx->GREATER_THAN())
        return make_unique<BinaryExpression>(
            get_source(ctx->GREATER_THAN()->getSymbol()),
            BinaryOperator::GREATER,
            move(left),
            move(right)
        );
    if(ctx->EQUIVALENT())
        return make_unique<BinaryExpression>(
            get_source(ctx->EQUIVALENT()->getSymbol()),
            BinaryOperator::EQUIVALENT,
            move(left),
            move(right)
        );
    
    throw runtime_error("Unknow comparaision");
}

unique_ptr<Expression> AstBuilder::build_or(HoihoiParser::OrContext* ctx) {
    if(ctx->and_().empty())
        throw runtime_error("No expression found in the or");
    
    auto left = build_and(ctx->and_()[0]);

    for(size_t i = 1UL; i < ctx->and_().size(); ++i) {
        auto right = build_and(ctx->and_()[i]);

        left = make_unique<BinaryExpression>(
            get_source(ctx->OR(i - 1)->getSymbol()),
            BinaryOperator::OR,
            move(left),
            move(right)
        );
    }

    return left;
}

unique_ptr<Expression> AstBuilder::build_and(HoihoiParser::AndContext* ctx) {  
    if(ctx->addition().empty()) {
        auto left = build_compaission(ctx->comparaision(0));

        for(size_t i = 1UL; i < ctx->comparaision().size(); ++i) {
            auto right = build_compaission(ctx->comparaision(i));

            left = make_unique<BinaryExpression>(
                get_source(ctx->AND(i - 1)->getSymbol()),
                BinaryOperator::AND,
                move(left),
                move(right)
            );
        }

        return left;
    }

    if(ctx->comparaision().empty()) {
        auto left = build_addition(ctx->addition(0));

        for(size_t i = 1UL; i < ctx->addition().size(); ++i) {
            auto right = build_addition(ctx->addition(i));

            left = make_unique<BinaryExpression>(
                get_source(ctx->AND(i - 1)->getSymbol()),
                BinaryOperator::AND,
                move(left),
                move(right)
            );
        }

        return left;    
    }

    throw runtime_error("You missing expression in and");
}

unique_ptr<Expression> AstBuilder::build_multiplication(HoihoiParser::MultiplicationContext* ctx) {
    if(ctx->attribute().empty())
        throw runtime_error("No expressions found");
    
    auto left = build_attribute(ctx->attribute(0));

    for(size_t i = 1UL; i < ctx->attribute().size(); ++i) {
        auto right = build_attribute(ctx->attribute(i));

        BinaryOperator op;
        SourceLocation location;

        if(ctx->STAR(i - 1)) {
            op = BinaryOperator::MUL;
            location = get_source(ctx->STAR(i - 1)->getSymbol());
        } else if(ctx->SLASH(i - 1)) {
            op = BinaryOperator::DIV;
            location = get_source(ctx->SLASH(i - 1)->getSymbol());
        } else if(ctx->MODULO(i - 1)) {
            op = BinaryOperator::MODULO;
            location = get_source(ctx->MODULO(i - 1)->getSymbol());
        }

        left = make_unique<BinaryExpression>(
            location,
            op,
            move(left),
            move(right)
        );
    }

    return left;
}

unique_ptr<Expression> AstBuilder::build_addition(HoihoiParser::AdditionContext* ctx) {
    if(ctx->multiplication().empty())
        throw runtime_error("No expressions found");
    
    auto left = build_multiplication(ctx->multiplication()[0]);

    for(size_t i = 1UL; i < ctx->multiplication().size(); ++i) {
        auto right = build_multiplication(ctx->multiplication()[i]);

        BinaryOperator op;
        SourceLocation location;

        if(ctx->PLUS(i - 1)) {
            op = BinaryOperator::PLUS;
            location = get_source(ctx->PLUS(i - 1)->getSymbol());
        } else if(ctx->MINUS(i - 1)) {
            op = BinaryOperator::MINUS;
            location = get_source(ctx->MINUS(i - 1)->getSymbol());
        }

        left = make_unique<BinaryExpression>(
            location,
            op,
            move(left),
            move(right)
        );
    }

    return left;
}

unique_ptr<Expression> AstBuilder::build_primary(HoihoiParser::PrimaryContext* ctx) {
    if(ctx->IDENTIFIER())
        return make_unique<Variable>(
            get_source(ctx->IDENTIFIER()->getSymbol()),
            ctx->IDENTIFIER()->getText()
        );
    else if(ctx->fun())
        return build_function(ctx->fun());
    else if(ctx->expr())
        return build_expression(ctx->expr());
    else if(ctx->cluster())
        return build_cluster(ctx->cluster());
    else if(ctx->EMPTY()) {
        vector<unique_ptr<Expression>> values;
        return make_unique<ClusterLiteral>(get_source(ctx->EMPTY()->getSymbol()), move(values));
    }
    
    throw runtime_error("Unknow primary expression");
}

unique_ptr<Expression> AstBuilder::build_cluster(HoihoiParser::ClusterContext* ctx) {
    vector<unique_ptr<Expression>> values;

    if(ctx->vector()->primitive())
        values.push_back(build_primitive(ctx->vector()->primitive()));

    vector<HoihoiParser::ElementContext*> elements;
    KindCluster kind;

    if(ctx->vector()) {
        elements = ctx->vector()->element();
        kind = KindCluster::VECTOR;
    } else if(ctx->bag()) {
        elements = ctx->bag()->element();
        kind = KindCluster::BAG;
    }


    for(auto* elem: elements) {
        if(elem->primitive())
            values.push_back(build_primitive(elem->primitive()));
        else
            values.push_back(build_expression(elem->expr()));
    }

    return make_unique<ClusterLiteral>(get_source(ctx->getStart()), move(values), kind, false);
}

unique_ptr<Expression> AstBuilder::build_function(HoihoiParser::FunContext* ctx) {
    vector<unique_ptr<Expression>> args;

    for(auto* exp: ctx->expr())
        args.push_back(move(build_expression(exp)));

    if(ctx->IDENTIFIER()->getText() == "tuple") {
        return make_unique<ClusterLiteral>(
            get_source(ctx->getStart()),
            move(args),
            KindCluster::TUPLE,
            false
        );
    } else if(ctx->IDENTIFIER()->getText() == "set") {
        return make_unique<ClusterLiteral>(
            get_source(ctx->getStart()),
            move(args),
            KindCluster::SET,
            false
        );
    }
  
    return make_unique<Function>(
        get_source(ctx->IDENTIFIER()->getSymbol()),
        ctx->IDENTIFIER()->getText(),
        move(args)
    );
}

unique_ptr<Expression> AstBuilder::build_attribute(HoihoiParser::AttributeContext* ctx) {
    auto primary = build_primary(ctx->primary());

    if(!ctx->fun() && !ctx->expr() && !ctx->IDENTIFIER())
        return primary;

    unique_ptr<Expression> name = nullptr;
    vector<unique_ptr<Expression>> args;
    KindAttribute kind;

    if(ctx->IDENTIFIER()) {
        name = make_unique<Primitive>(
            get_source(ctx->IDENTIFIER()->getSymbol()),
            ctx->IDENTIFIER()->toString()
        );

        kind = KindAttribute::GET;
    } else if(ctx->expr()) {
        name = build_expression(ctx->expr());
        
        kind = KindAttribute::GET;
    } else {
        name = make_unique<Primitive>(
            get_source(ctx->fun()->IDENTIFIER()->getSymbol()),
            ctx->fun()->IDENTIFIER()->toString()
        );

        kind = (ctx->DOT())? KindAttribute::CALL : KindAttribute::SELF_CALL;

        for(auto* arg: ctx->fun()->expr())
            args.push_back(move(build_expression(arg)));
    }

    return make_unique<Attribute>(
        get_source(ctx->getStart()),
        move(primary),
        move(name),
        kind,
        move(args)
    );
}

std::unique_ptr<Expression> AstBuilder::build_primitive(HoihoiParser::PrimitiveContext* ctx) {
    return make_unique<Primitive>(
        get_source(ctx->getStart()),
        build_instance_primitive(ctx)
    );
}

InstancePrimitive AstBuilder::build_instance_primitive(HoihoiParser::PrimitiveContext* ctx) {
    if(ctx->HIGH()) return TernaryLogical::HIGH;
    if(ctx->NEUTRAL()) return TernaryLogical::NEUTRAL;
    if(ctx->LOW()) return TernaryLogical::LOW;
    
    if(!ctx->number()) {
        auto s = ctx->STRING_LITERAL()->getText();
        s.erase(
            remove_if(s.begin(), s.end(), [](char c) { return c == '"' || c == '\'' || c == '\\'; }),
            s.end()
        );

        return s;
    }

    if(ctx->number()->FLOAT_LITERAL())
        return stod(ctx->number()->FLOAT_LITERAL()->getText());

    if(ctx->number()->INTEGER_LITERAL())
        return stol(ctx->number()->INTEGER_LITERAL()->getText());

    throw runtime_error("Unknow primitive");
}
