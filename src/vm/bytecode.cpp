#include "vm/bytecode.hpp"
#include "value/value.hpp"

#include <iostream>

using namespace std;
using namespace hoihoi;

string Bytecode::to_string() const {
    string tmp = "co_names = {";

    for(size_t i = 0UL; i < co_names.size(); i++) {
        tmp += co_names.at(i);

        if(i < co_names.size() - 1) tmp += ",";
    }

    tmp += "}\n";

    for(const Instruction& instr: this->m_instruction) {
        tmp += to_string_opcode(instr.opcode) + " ";

        if(instr.opcode == Opcode::CONST_CHAR)
            tmp += string(1, static_cast<char>(instr.operand));
        else if((instr.opcode == Opcode::LOAD_GLOBAL) || ((instr.opcode == Opcode::STORE_GLOBAL))) {
            tmp += std::to_string(instr.operand) + " (" + get_name(instr.operand) + ")";
        } else if(instr.opcode == Opcode::LOAD_CONST) {
            tmp += std::to_string(instr.operand) + " (" + get_const(instr.operand)->to_string() + ")";
        } else {
            tmp += std::to_string(instr.operand);
        }

        tmp += "\n";
    }

    return tmp;
}
