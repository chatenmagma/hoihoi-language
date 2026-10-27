#ifndef HOIHOI_INSTRUCTION_HPP
#define HOIHOI_INSTRUCTION_HPP

#include <cstdint>
#include <string>

namespace hoihoi {
    enum class BinaryOperator: std::uint8_t {
        PLUS,
        MINUS,
        MUL,
        DIV,
        MODULO,

        EQUAL,
        NOT_EQUAL,
        LOWER,
        GREATER,
        EQUIVALENT,
        
        OR,
        AND
    };
    
    enum class Opcode {
        NOP,
        HALT,

        CONST_OBJ,

        CONST_INTEGER32,
        CONST_INTEGER64_LOWER,
        CONST_INTEGER64_HIGHER,

        CONST_FLOAT_LOWER,
        CONST_FLOAT_HIGHER,
        CONST_CHAR,
        CONST_LOGICAL,
        CONST_THING,

        BUILD_FUNCTION,
        BUILD_STRING,

        BUILD_BAG,
        BUILD_SET,
        BUILD_TUPLE,
        BUILD_VECTOR,

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
        BINARY_OP,
        ASSIGN_BINARY_OP
    };

    inline std::string to_string_opcode(Opcode op) {
        switch(op) {
            case Opcode::NOP: return "NOP"; 
            case Opcode::HALT: return "HALT"; 
            case Opcode::CONST_OBJ: return "CONST_OBJ"; 
            case Opcode::CONST_INTEGER32: return "CONST_INTEGER32"; 
            case Opcode::CONST_INTEGER64_LOWER: return "CONST_INTEGER64_LOWER"; 
            case Opcode::CONST_INTEGER64_HIGHER: return "CONST_INTEGER64_HIGHER"; 
            case Opcode::CONST_FLOAT_LOWER: return "CONST_FLOAT_LOWER"; 
            case Opcode::CONST_FLOAT_HIGHER: return "CONST_FLOAT_HIGHER"; 
            case Opcode::CONST_CHAR: return "CONST_CHAR"; 
            case Opcode::CONST_LOGICAL: return "CONST_LOGICAL";
            case Opcode::CONST_THING: return "CONST_THING";

            case Opcode::BUILD_FUNCTION: return "BUILD_FUNCTION";
            case Opcode::BUILD_STRING: return "BUILD_STRING"; 
            
            case Opcode::BUILD_BAG: return "BUILD_BAG";
            case Opcode::BUILD_SET: return "BUILD_SET";
            case Opcode::BUILD_TUPLE: return "BUILD_TUPLE";
            case Opcode::BUILD_VECTOR: return "BUILD_VECTOR";

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
            case Opcode::ASSIGN_BINARY_OP: return "ASSIGN_BINARY_OP";
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
