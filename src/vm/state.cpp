#include "vm/state.hpp"

#include "compiler/compiler.hpp"

using namespace hoihoi;
using namespace std;

Runtime State::runtime = Runtime();

int State::execute(const std::string& source_code) {
    this->frames.clear();
    this->frames.emplace_back(Compiler::compile(source_code));

    for(;;) {
        Instruction inst = get_current_frame().code.get_instruction(get_current_frame().pc);

        switch(inst.opcode) {
            case Opcode::NOP: break;
            case Opcode::STORE_GLOBAL:
                variables[get_current_frame().code.get_name(inst.operand)] = pop();
            break;
            case Opcode::STORE_LOCAL:
                get_current_frame().locals[inst.operand] = pop();
            break;
            case Opcode::LOAD_GLOBAL:
                if(variables.contains(get_current_frame().code.get_name(inst.operand)))
                    push(variables[get_current_frame().code.get_name(inst.operand)]);
                else {
                    cerr << "Not definied the global variable `" << get_current_frame().code.get_name(inst.operand) << "`\n";
                    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            break;
            case Opcode::LOAD_CONST:
                push(get_current_frame().code.get_const(inst.operand));
            break;
            case Opcode::LOAD_LOCAL:
                push(get_current_frame().locals.at(inst.operand));
            break;
            case Opcode::LOAD_ATTRIBUTE: {
                try {
                    push(pop()->get_class()->get_attribute(pop()->to_string()));
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    cerr << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            } break;
            case Opcode::LOAD_ATTRIBUTE_KEEP: {
                try {
                    auto keep = pop();
                    push(keep->get_class()->get_attribute(pop()->to_string()));
                    push(keep); // ref
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    cerr << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            } break;

            case Opcode::CALL: {
                vector<ObjectPtr> args = vector<ObjectPtr>(inst.operand);

                for(int32_t i = 0UL; i < inst.operand; i++)
                    args[inst.operand - 1 - i] = pop();
                
                auto* fun = dynamic_cast<Terminal*>(pop().get());

                if(!fun) {
                    cerr << "Must a cluster function or builtin not a " <<  fun->to_string() << '\n';
                    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }

                const auto& val = fun->get_value();

                if(auto* builtin = get_if<shared_ptr<Builtin>>(&val)) {
                    try {
                        if(auto res = builtin->get()->operator()(args)) push(res);
                        break;
                    } catch(exception& e) {
                        cerr << e.what() << "\n";
                        cerr << "From line  " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                        return 1;
                    }
                } else if(auto* bytecode = get_if<shared_ptr<Bytecode>>(&val)) {
                    call_frame(*bytecode->get(), args);
                    get_current_frame().pc--;
                } else {
                    cerr << "Must a cluster function or builtin not a " <<  fun->to_string() << '\n';
                    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            } break;
            case Opcode::RETURN: this->call_back(); break;
            
            case Opcode::JUMP_ABSOLUTE: get_current_frame().pc += inst.operand; break;
            case Opcode::JUMP_IF_FALSE: if(!pop()->is_high()) get_current_frame().pc += inst.operand; break;

            case Opcode::CONST_NUMBER: push(make_shared<String>(std::to_string(inst.operand))); break;
            case Opcode::CONST_CHAR: push(make_shared<Terminal>(Class::terminal_character, static_cast<char>(inst.operand))); break;

            case Opcode::BUILD_FLAT: push(make_shared<ClusterOrdered>()); break;
        
            case Opcode::BUILD_FUNCTION: push(get_current_frame().code.get_const(inst.operand)); break;

            case Opcode::BUILD_STRING:
            case Opcode::BUILD_HEAP:
            case Opcode::BUILD_HOLE:{
                vector<ObjectPtr> val = vector<ObjectPtr>(inst.operand);

                for(int32_t i = 0; i < inst.operand; i++)
                    val[inst.operand - 1 - i] = pop();
                
                if(Opcode::BUILD_STRING == inst.opcode)
                    push(make_shared<String>(move(val)));
                else
                    push(make_shared<ClusterOrdered>(move(val), Opcode::BUILD_HOLE == inst.opcode));
            }break;
            case Opcode::BUILD_LOGICAL:
                push(make_shared<Terminal>(Class::terminal_logical, static_cast<TernaryLogical>(inst.operand)));
            break;

            case Opcode::UNARY_OP:{
                try {
                    auto res = pop()->copy();

                    switch(static_cast<UnaryOperator>(inst.operand)) {
                        case UnaryOperator::NOT: res->opposite(); break;
                    }

                    push(res);
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            }break;

            case Opcode::BINARY_OP:{
                try {
                    auto valB = pop();
                    auto res = pop()->copy();

                    switch(static_cast<BinaryOperator>(inst.operand)) {
                        case BinaryOperator::PLUS: res->add(valB); break;
                        case BinaryOperator::MINUS: res->sub(valB); break;
                        case BinaryOperator::MUL: res->mul(valB); break;
                        case BinaryOperator::DIV: res->div(valB); break;
                        case BinaryOperator::MODULO: break;

                        case BinaryOperator::EQUAL: 
                            res = make_shared<Terminal>(
                                Class::terminal_logical, 
                                res->equal(valB)? TernaryLogical::HIGH: TernaryLogical::LOW
                            ); 

                            break;
                        case BinaryOperator::NOT_EQUAL: 
                            res = make_shared<Terminal>(
                                Class::terminal_logical, 
                                res->equal(valB)? TernaryLogical::HIGH: TernaryLogical::LOW
                            ); 

                            res->opposite();
                            
                            break;
                        case BinaryOperator::OR: res = res->or_operation(valB); break;
                        case BinaryOperator::AND: res = res->and_operation(valB); break;

                        case BinaryOperator::LOWER: res = res->lower_operation(valB); break;
                        case BinaryOperator::GREATER: res = res->greater_operation(valB); break;
                    }

                    push(res);
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
                    return 1;
                }
            }break;
            
            case Opcode::HALT: return inst.operand;
            default: throw runtime_error("Unknown instruction");
        }

        get_current_frame().pc++;
    }

    return 0;
}
