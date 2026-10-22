#ifndef HOIHOI_INSTRUCTION_HPP
#define HOIHOI_INSTRUCTION_HPP

#include <cstdint>
#include <string>

namespace hoihoi {
    enum class Opcode {
        NOP,
        HALT,

        CONST_OBJ,
        CONST_NUMBER,
        CONST_CHAR,

        BUILD_FUNCTION,
        BUILD_STRING,

        BUILD_HEAP,
        BUILD_FLAT,
        BUILD_HOLE,
        BUILD_LOGICAL,

        PUSH,
        POP,

        LOAD_CONST,
        LOAD_GLOBAL,
        LOAD_LOCAL,
        LOAD_ATTRIBUTE,
        LOAD_ATTRIBUTE_KEEP,
        STORE_GLOBAL,
        STORE_LOCAL,

        JUMP_IF_FALSE,
        JUMP_ABSOLUTE,

        CALL,
        RETURN,

        UNARY_OP,
        BINARY_OP
    };

    inline std::string to_string_opcode(Opcode op) {
        switch(op) {
            case Opcode::NOP: return "NOP"; 
            case Opcode::HALT: return "HALT"; 
            case Opcode::CONST_OBJ: return "CONST_OBJ"; 
            case Opcode::CONST_NUMBER: return "CONST_NUMBER"; 
            case Opcode::CONST_CHAR: return "CONST_CHAR"; 
            case Opcode::BUILD_FUNCTION: return "BUILD_FUNCTION";
            case Opcode::BUILD_STRING: return "BUILD_STRING"; 
            case Opcode::BUILD_HEAP: return "BUILD_HEAP"; 
            case Opcode::BUILD_FLAT: return "BUILD_FLAT"; 
            case Opcode::BUILD_HOLE: return "BUILD_HOLE";
            case Opcode::BUILD_LOGICAL: return "BUILD_LOGICAL";
            case Opcode::PUSH: return "PUSH"; 
            case Opcode::POP: return "POP"; 
            case Opcode::LOAD_CONST: return "LOAD_CONST"; 
            case Opcode::LOAD_GLOBAL: return "LOAD_GLOBAL"; 
            case Opcode::LOAD_LOCAL: return "LOAD_LOCAL";
            case Opcode::LOAD_ATTRIBUTE: return "LOAD_ATTRIBUTE";
            case Opcode::LOAD_ATTRIBUTE_KEEP: return "LOAD_ATTRIBUTE_KEEP";
            case Opcode::STORE_GLOBAL: return "STORE_GLOBAL"; 
            case Opcode::STORE_LOCAL: return "STORE_LOCAL";
            case Opcode::JUMP_IF_FALSE: return "JUMP_IF_FALSE"; 
            case Opcode::JUMP_ABSOLUTE: return "JUMP_ABSOLUTE"; 
            case Opcode::CALL: return "CALL"; 
            case Opcode::RETURN: return "RETURN"; 
            case Opcode::UNARY_OP: return "UNARY_OP";
            case Opcode::BINARY_OP: return "BINARY_OP";
        }

        return "NOT_DEF_BUT_NOP";
    }

    struct Instruction {
        Opcode opcode;
        std::int32_t operand;

        Instruction(Opcode opcode, std::int32_t operand)
            : opcode(opcode), operand(operand) {}
        Instruction(Opcode opcode)
            : opcode(opcode), operand(0) {}
        ~Instruction() = default;
    };
}

#endif /* HOIHOI_INSTRUCTION_HPP */
