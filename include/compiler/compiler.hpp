#ifndef HOIHOI_COMPILER_HPP
#define HOIHOI_COMPILER_HPP

#include "table_symbol.hpp"
#include "parser/ast_builder.hpp"

namespace hoihoi {
    class Compiler {
        private:
            TableSymbol symbol;
            Bytecode code;

            std::size_t compile_statement(const Statement& statement);
            std::size_t compile_expression(const Expression& expression);

            std::size_t compile_function_declaration(const FunctionDeclaration& declaration);

            std::size_t compile_if_statement(const IfStatement& if_stmt);
            std::size_t compile_while_statement(const WhileStatement& while_stmt);

            std::size_t compile_primitive(const InstancePrimitive prim);
        public:
            Compiler(const program& prog) {
                symbol.scan(prog, 0UL);
                insert_globals(symbol);
                compile_code(prog);
            }
            Compiler(const program& prog, TableSymbol symbol)
                : symbol(symbol) {
                insert_globals(symbol);
                compile_function(prog);
            }
            ~Compiler() = default;

            void insert_globals(const TableSymbol& symbol);

            inline static Bytecode compile(const std::string& source_code) {
                return Compiler(AstBuilder::build(source_code)).get_bytecode();
            }

            inline void compile_code(const program& prog) { 
                std::for_each(prog.begin(), prog.end(), [&](const auto& stmt) { compile_statement(*stmt); }); 
                code.emit_instruction(Opcode::HALT);
            }

            inline void compile_function(const program& prog) {
                std::for_each(prog.begin(), prog.end(), [&](const auto& stmt) { compile_statement(*stmt); }); 
                code.emit_instruction(Opcode::RETURN);
            }

            inline Bytecode get_bytecode() { return code; }
    };
}

#endif /* HOIHOI_COMPILER_HPP */
