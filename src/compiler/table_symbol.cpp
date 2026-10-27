#include "compiler/table_symbol.hpp"

using namespace hoihoi;
using namespace std;

TableSymbol::TableSymbol(const vector<string>& __locals) {
    for(const string& l: __locals)
        this->local.push_back(l);
}

void TableSymbol::scan_statement(const Statement& stmt, size_t scope) {
    if(auto* assign = dynamic_cast<const AssignementStatement*>(&stmt)) {
        if(is_in_global_scope(scope)) this->global.insert(assign->name);
        else if(!this->global.contains(assign->name)) {
            this->local.push_back(assign->name);
        }

        scan_expression(*assign->expression, scope);
    }

    if(auto* expr = dynamic_cast<const ExpressionStatement*>(&stmt))
        scan_expression(*expr->expression, scope);

    if(auto* ret = dynamic_cast<const ReturnStatement*>(&stmt))
        if(ret->expression) scan_expression(*ret->expression, scope);

    if(auto* if_stmt = dynamic_cast<const IfStatement*>(&stmt)) {
        scan_expression(*if_stmt->condition, scope);

        for(const auto& b: if_stmt->body) scan_statement(*b, scope);
        for(const auto& b: if_stmt->body_else) scan_statement(*b, scope);
    }

    if(auto* while_stmt = dynamic_cast<const WhileStatement*>(&stmt)) {
        scan_expression(*while_stmt->condition, scope);

        for(const auto& b: while_stmt->body) scan_statement(*b, scope);
    }

    if(auto* fun_stmt = dynamic_cast<const FunctionDeclaration*>(&stmt)) {
        if(is_in_global_scope(scope)) this->global.insert(fun_stmt->name);
        else this->local.push_back(fun_stmt->name);
    }
}

void TableSymbol::scan_expression(const Expression& expr, size_t scope) {
    if(auto* var = dynamic_cast<const Variable*>(&expr))
        if(is_in_global_scope(scope))
            this->global.insert(var->name);
        else if(count(local.begin(), local.end(), var->name) == 0)
            this->global.insert(var->name);

    if(auto* fun = dynamic_cast<const Function*>(&expr)) {
        if(is_in_global_scope(scope)) this->global.insert(fun->name);
        else if(count(local.begin(), local.end(), fun->name) == 0)
            this->global.insert(fun->name);
        
        for(const auto& expr: fun->args)
            scan_expression(*expr, scope);
    }

    if(auto* cluster_litteral = dynamic_cast<const ClusterLiteral*>(&expr))
        for(const auto& expr: cluster_litteral->values)
            scan_expression(*expr, scope);

    if(auto* attribute = dynamic_cast<const Attribute*>(&expr)) {
        scan_expression(*attribute->value, scope);
        scan_expression(*attribute->name, scope);
    }

    if(auto* unary = dynamic_cast<const UnaryExpression*>(&expr))
        scan_expression(*unary->value, scope);

    if(auto* bin = dynamic_cast<const BinaryExpression*>(&expr)) {
        scan_expression(*bin->left, scope);
        scan_expression(*bin->right, scope);
    }
}
