#include "ast/ast.hpp"

#include <iostream>
#include <algorithm>

using namespace hoihoi;
using namespace std;

void AstPrinter::print(const program& prog) {
    for(const auto& stat: prog)
        AstPrinter::print_statement(*stat, 0);
}

void AstPrinter::print_statement(const Statement& stmt, int indent) {
    if(auto* assign = dynamic_cast<const AssignementStatement*>(&stmt)) {
        print_indent(indent);
        cout << "Assignement: " << assign->name << ":" << endl;
        print_expression(*assign->expression, indent + 2);
    } else if(auto* expr = dynamic_cast<const ExpressionStatement*>(&stmt)) {
        print_indent(indent);
        cout << "Expression Statement:" << endl;
        print_expression(*expr->expression, indent + 2);
    } else if(auto* ifStmt = dynamic_cast<const IfStatement*>(&stmt)) {
        print_indent(indent);
        cout << "If Statement:\n";
        
        print_indent(indent + 2);
        cout << "condition:\n";
        print_expression(*ifStmt->condition, indent + 4);

        print_indent(indent + 2);
        cout << "body" << endl;

        for(const auto& body_stmt: ifStmt->body)
            print_statement(*body_stmt, indent + 4);
        
        if(!ifStmt->body_else.empty()) {
            print_indent(indent + 2);
            cout << "else:" << endl;

            for(const auto& else_stmt: ifStmt->body_else)
                print_statement(*else_stmt, indent + 4);
        }
        
    } else if(dynamic_cast<const PassStatement*>(&stmt)) {
        print_indent(indent + 2);
        cout << "Pass Statement" << endl;
    } else if(auto* returnStmt = dynamic_cast<const ReturnStatement*>(&stmt)) {
        print_indent(indent);
        cout << "Return Statement" << endl;

        if(returnStmt->expression) {
            print_indent(indent + 2);
            cout << "Expression return: " << endl;

            print_expression(*returnStmt->expression, indent + 4);
        }
    }
}

void AstPrinter::print_expression(const Expression& expr, int indent) {
    if(auto* var = dynamic_cast<const Variable*>(&expr)) {
        print_indent(indent);
        cout << "Variable: " << var->name << endl;
    } else if(auto* fun = dynamic_cast<const Function*>(&expr)) {
        print_indent(indent);
        cout << "Call function: " << fun->name << endl;

        for(const auto& arg: fun->args)
            print_expression(*arg, indent + 2);
    } else if(auto* binary = dynamic_cast<const BinaryExpression*>(&expr)) {
        print_indent(indent);
        cout << "Binary Expression:" << endl;

        print_expression(*binary->left, indent + 2);

        print_indent(indent + 2);
        switch(binary->op) {
            case BinaryOperator::PLUS: cout << '+' << endl; break;
            case BinaryOperator::MINUS: cout << '-' << endl; break;
            case BinaryOperator::MUL: cout << '*' << endl; break;
            case BinaryOperator::DIV: cout << '/' << endl; break;
            case BinaryOperator::MODULO: cout << '%' << endl; break;

            case BinaryOperator::EQUAL: cout << "==" << endl; break;
            case BinaryOperator::NOT_EQUAL: cout << "!=" << endl; break;
            case BinaryOperator::OR: cout << "||" << endl; break;
            case BinaryOperator::AND: cout << "&&" << endl; break;
            case BinaryOperator::LOWER: cout << "<" << endl; break;
            case BinaryOperator::GREATER: cout << ">" << endl; break;
            case BinaryOperator::EQUIVALENT: cout << "<>" << endl; break;
        }

        print_expression(*binary->right, indent + 2);
    } 
}

void AstPrinter::print_indent(int indent) {
    for(int i = 0; i < indent; i++)
        cout << ' ';
}
