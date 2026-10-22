#ifndef HOIHOI_BYTECODE_HPP
#define HOIHOI_BYTECODE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "source_location.hpp"
#include "value/object.hpp"

#include "instruction.hpp"

namespace hoihoi {
    class Bytecode {
        private:
            std::unordered_map<std::size_t, SourceLocation> source_locations;

            std::vector<Instruction> m_instruction;
            std::vector<std::string> co_names;
            std::vector<ObjectPtr> co_const;

            std::size_t nb_local = 0UL;
        public:
            Bytecode() = default;
            ~Bytecode() = default;

            inline std::size_t get_nb_local() const noexcept { return nb_local; }
            inline void set_nb_local(std::size_t __nb_local__) noexcept { nb_local = __nb_local__; }

            inline std::size_t emit_instruction(Opcode opcode, std::int32_t operande = 0) {
                m_instruction.emplace_back(opcode, operande);
                return m_instruction.size() - 1;
            }

            inline std::size_t emit_name(const std::string& name) {
                co_names.emplace_back(name);
                return co_names.size() - 1;
            }

            inline std::size_t emit_const(ObjectPtr ptr) {
                co_const.emplace_back(ptr);
                return co_const.size() - 1;
            }

            inline void emit_source_location(std::size_t index, SourceLocation location) {
                source_locations[index] = location;
            }

            inline Instruction get_instruction(std::size_t index) const { return m_instruction.at(index); }
            inline Instruction& get_instruction(std::size_t index) { return m_instruction.at(index); }
            inline std::string get_name(std::size_t index) const { 
                if(index >= co_names.size()) 
                    throw std::overflow_error(
                        "Cannot at in index " + std::to_string(index) + " because you have only " + std::to_string(co_names.size()) + " names"
                    );
                return co_names.at(index); 
            }
            inline ObjectPtr get_const(std::size_t index) const {
                if(index >= co_const.size()) 
                    throw std::overflow_error(
                        "Cannot at in index " + std::to_string(index) + " because you have only " + std::to_string(co_const.size()) + " const"
                    );
                    
                return co_const.at(index);
            }

            inline SourceLocation get_source_location(std::size_t index) { return source_locations[index]; }

            inline std::size_t size() const noexcept { return m_instruction.size(); }

            std::string to_string() const;
    };
}

#endif /* HOIHOI_BYTECODE_HPP */
