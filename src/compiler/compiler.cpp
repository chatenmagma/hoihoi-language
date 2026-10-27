#include <iostream>
#include <bit>

#include "compiler/compiler.hpp"
#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

void Compiler::insert_globals(const TableSymbol& __symbol) {
    for(const auto& global: __symbol.get_globals())
        code.emit_name(global);
    code.set_nb_local(__symbol.get_locals().size());
}

size_t Compiler::compile_statement(const Statement& stmt) {
    if(auto* assign_op = dynamic_cast<const AssignementOperationStatement*>(&stmt)) {
        switch(symbol.get_type(assign_op->name)) {
            case VariableType::GLOBAL: code.emit_instruction(Opcode::LOAD_GLOBAL, symbol.get_index(assign_op->name)); break;
            case VariableType::LOCAL: code.emit_instruction(Opcode::LOAD_LOCAL, symbol.get_index(assign_op->name)); break;
        }

        size_t nb = compile_expression(*assign_op->expression);

        code.emit_instruction(Opcode::ASSIGN_BINARY_OP, static_cast<int32_t>(assign_op->op));

        return nb + 2;
    }

    if(auto* assign = dynamic_cast<const AssignementStatement*>(&stmt)) {
        size_t nb = compile_expression(*assign->expression);

        switch(symbol.get_type(assign->name)) {
            case VariableType::GLOBAL: code.emit_instruction(Opcode::STORE_GLOBAL, symbol.get_index(assign->name)); break;
            case VariableType::LOCAL: code.emit_instruction(Opcode::STORE_LOCAL, symbol.get_index(assign->name)); break;
        }

        return nb + 1;
    }

    if(auto* expr = dynamic_cast<const ExpressionStatement*>(&stmt))
        return compile_expression(*expr->expression);

    if(auto* ifStmt = dynamic_cast<const IfStatement*>(&stmt))
        return compile_if_statement(*ifStmt);

    if(auto* whileStmt = dynamic_cast<const WhileStatement*>(&stmt)) 
        return compile_while_statement(*whileStmt);

    if(auto* fun_def = dynamic_cast<const FunctionDeclaration*>(&stmt)) {
        TableSymbol new_table = TableSymbol(fun_def->args);
        
        new_table.scan(fun_def->body, 1);

        Compiler compile_function = Compiler(fun_def->body, new_table);


        code.emit_instruction(
            Opcode::LOAD_CONST, 
            code.emit_const(make_shared<Terminal>(Class::terminal_funtion, make_shared<Bytecode>(move(compile_function.get_bytecode()))))
        );

        switch(symbol.get_type(fun_def->name)) {
            case VariableType::GLOBAL: code.emit_instruction(Opcode::STORE_GLOBAL, symbol.get_index(fun_def->name)); break;
            case VariableType::LOCAL: code.emit_instruction(Opcode::STORE_LOCAL, symbol.get_index(fun_def->name)); break;
        }

        return 2;
    }

    if(auto* ret = dynamic_cast<const ReturnStatement*>(&stmt)) {
        size_t nb = (!ret->expression)? 0UL: compile_expression(*ret->expression);

        code.emit_instruction(Opcode::RETURN);

        return nb + 1;
    }

    return 0;
}

size_t Compiler::compile_primitive(const InstancePrimitive prim) {
    if(holds_alternative<double>(prim)) {
        code.emit_instruction(Opcode::CONST_FLOAT_LOWER, static_cast<int32_t>(bit_cast<int64_t>(get<double>(prim))));
        code.emit_instruction(Opcode::CONST_FLOAT_HIGHER, static_cast<int32_t>(bit_cast<int64_t>(get<double>(prim)) >> 32UL));

        return 2UL;
    } else if(holds_alternative<std::int64_t>(prim)) {
        if(get<int64_t>(prim) > 2147483647 || get<int64_t>(prim) < -2147483648) {
            code.emit_instruction(Opcode::CONST_INTEGER64_LOWER, get<int64_t>(prim));
            code.emit_instruction(Opcode::CONST_INTEGER64_HIGHER, get<int64_t>(prim) >> 32UL);

            return 2UL;
        }
        
        code.emit_instruction(Opcode::CONST_INTEGER32, static_cast<int32_t>(get<int64_t>(prim)));

        return 1UL;
    } else if(holds_alternative<TernaryLogical>(prim)) {
        code.emit_instruction(Opcode::CONST_LOGICAL, static_cast<int32_t>(get<TernaryLogical>(prim)));
        
        return 1UL;
    } else if(holds_alternative<string>(prim)) {
        size_t nb = 0UL;

        for(char chr: get<string>(prim)) {
            code.emit_instruction(Opcode::CONST_CHAR, static_cast<int32_t>(chr));
            nb += 1UL;
        }

        code.emit_instruction(Opcode::BUILD_STRING, get<string>(prim).size());
        
        return nb + 1UL;
    }

    return 0UL;
}

size_t Compiler::compile_expression(const Expression& expr) {
    if(auto* primitive = dynamic_cast<const Primitive*>(&expr))
        return compile_primitive(primitive->value);

    if(auto* var = dynamic_cast<const Variable*>(&expr)) {
        size_t pos;
        switch(symbol.get_type(var->name)) {
            case VariableType::GLOBAL: pos = code.emit_instruction(Opcode::LOAD_GLOBAL, symbol.get_index(var->name)); break;
            case VariableType::LOCAL: pos = code.emit_instruction(Opcode::LOAD_LOCAL, symbol.get_index(var->name)); break;
        }

        code.emit_source_location(pos, var->location);

        return 1;
    }

    if(auto* fun = dynamic_cast<const Function*>(&expr)) {
        size_t nb = 1;

        size_t pos;
        switch(symbol.get_type(fun->name)) {
            case VariableType::GLOBAL: pos = code.emit_instruction(Opcode::LOAD_GLOBAL, symbol.get_index(fun->name)); break;
            case VariableType::LOCAL: pos = code.emit_instruction(Opcode::LOAD_LOCAL, symbol.get_index(fun->name)); break;
        }

        code.emit_source_location(pos, fun->location);

        for(const auto& arg: fun->args)
            nb += compile_expression(*arg);

        code.emit_source_location(
            code.emit_instruction(Opcode::CALL, fun->args.size()), 
            fun->location
        );

        return nb + 1;
    }

    if(auto* attribute = dynamic_cast<const Attribute*>(&expr)) {
        size_t nb = compile_expression(*attribute->name) + compile_expression(*attribute->value);

        code.emit_source_location(
            code.emit_instruction(
                (attribute->kind == KindAttribute::SELF_CALL)? Opcode::LOAD_ATTRIBUTE_KEEP: Opcode::LOAD_ATTRIBUTE),
            attribute->location
        );

        if(attribute->kind == KindAttribute::GET) return nb + 1;

        for(const auto& a: attribute->args)
            nb += compile_expression(*a);
        
        code.emit_source_location(
            code.emit_instruction(Opcode::CALL, attribute->args.size() + ((attribute->kind == KindAttribute::CALL)? 0UL: 1UL)),
            attribute->location
        );

        return nb + 2;
    }

    if(auto* unary_op = dynamic_cast<const UnaryExpression*>(&expr)) {
        size_t nb = compile_expression(*unary_op->value);

        code.emit_source_location(
            code.emit_instruction(Opcode::UNARY_OP, static_cast<int>(unary_op->op)),
            unary_op->location
        );

        return nb + 1;
    }

    if(auto* binary_op = dynamic_cast<const BinaryExpression*>(&expr)) {
        size_t nb = 0;

        nb += compile_expression(*binary_op->left);
        nb += compile_expression(*binary_op->right);

        code.emit_source_location(
            code.emit_instruction(Opcode::BINARY_OP, static_cast<int32_t>(binary_op->op)), 
            binary_op->location
        );

        return nb + 1;
    }

    if(auto* cluster_literal = dynamic_cast<const ClusterLiteral*>(&expr)) {
        size_t nb = 0UL;
        size_t nb_elem = 0UL;

        for(const auto& expr: cluster_literal->values) {
            nb += compile_expression(*expr);
                
            nb_elem++;
        }

        Opcode opcode;
        switch (cluster_literal->kind) {
            case KindCluster::VECTOR: opcode = Opcode::BUILD_VECTOR; break;
            case KindCluster::BAG: opcode = Opcode::BUILD_BAG; break;
            case KindCluster::TUPLE: opcode = Opcode::BUILD_TUPLE; break;
            case KindCluster::SET: opcode = Opcode::BUILD_SET; break;
        }
        
        code.emit_instruction(opcode, nb_elem * ((cluster_literal->negative)? -1: 1));

        return nb + 1;
    }

    return 0;
}

std::size_t Compiler::compile_if_statement(const IfStatement& if_stmt) {
    size_t jumb_else_pos;

    size_t body_else_sz = 0;
    size_t body_sz = 0;

    // Compile expression and condition
    size_t nb = compile_expression(*if_stmt.condition) + 1;
    size_t jumb_pos = code.emit_instruction(Opcode::JUMP_IF_FALSE);

    // Compile the body if
    for(const auto& stmt_body: if_stmt.body)
        body_sz += compile_statement(*stmt_body);
    nb += body_sz;
    
    // Add instruction for bypas the else stmt
    if(!if_stmt.body_else.empty()) {
        jumb_else_pos = code.emit_instruction(Opcode::JUMP_ABSOLUTE);
        nb++;
    }
    
    // Number instruction to pass jump if false
    code.get_instruction(jumb_pos).operand = body_sz + (if_stmt.body_else.empty()? 0: 1);        
    
    // Compile the body else
    for(const auto& stmt_else: if_stmt.body_else)
        body_else_sz += compile_statement(*stmt_else);
    nb += body_else_sz;
        
    if(!if_stmt.body_else.empty())
        code.get_instruction(jumb_else_pos).operand = body_else_sz;

    return nb;
}

std::size_t Compiler::compile_while_statement(const WhileStatement& while_stmt) {
    // Compile expression and condition
    size_t nb = compile_expression(*while_stmt.condition) + 1;
    size_t jump_idx = code.emit_instruction(Opcode::JUMP_IF_FALSE);

    size_t body_size = 0UL;
    for(const auto& body_stmt: while_stmt.body)
        body_size += compile_statement(*body_stmt);
    nb += body_size + 1;

    code.emit_instruction(Opcode::JUMP_ABSOLUTE, -static_cast<int>(nb));
    code.get_instruction(jump_idx).operand = body_size + 1;

    return nb;
}
