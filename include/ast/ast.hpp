#pragma once

#include <unordered_map>
#include "statement.hpp"

namespace hoihoi {
    using program = std::vector<std::unique_ptr<Statement>>;

    class AstPrinter {
        private:
            static void print_statement(const Statement& statement, int indent);
            static void print_expression(const Expression& expression, int indent);
            static void print_indent(int indent);
        public:
            static void print(const program& prog);
    };

    struct Scope {
        size_t scope_pos;
        std::unordered_map<std::string, std::string> variables;
    };
}
