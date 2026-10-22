#pragma once

#include "ast/ast.hpp"
#include "vm/bytecode.hpp"

#include <algorithm>
#include <unordered_set>

namespace hoihoi {
    enum class VariableType: std::uint8_t {
        GLOBAL,
        LOCAL
    };

    class TableSymbol {
        private:
            std::unordered_set<std::string> global;
            std::vector<std::string> local;

            inline bool is_in_global_scope(std::size_t scope) const { return scope == 0UL; }

            void scan_statement(const Statement& stmt, std::size_t scope);
            void scan_expression(const Expression& expr, std::size_t scope);
        public:
            TableSymbol() = default;
            TableSymbol(const std::vector<std::string>& __locals);
            ~TableSymbol() = default;

            inline void scan(const program& prog, std::size_t scope) {
                for(const auto& stmt: prog) scan_statement(*stmt, scope);
            }

            inline const auto& get_globals() const { return global; }
            inline const auto& get_locals() const { return local; }

            inline VariableType get_type(const std::string& var_name) const noexcept {
                if(std::count(local.begin(), local.end(), var_name)) return VariableType::LOCAL;
                
                return VariableType::GLOBAL;
            }

            inline std::size_t get_index(const std::string& var_name) const {
                if(std::count(local.begin(), local.end(), var_name)) 
                    return std::distance(local.begin(), std::find(local.begin(), local.end(), var_name));

                return std::distance(global.begin(), global.find(var_name));
            }
    };
}
