#include "vm/state.hpp"
#include "vm/module.hpp"

#include "compiler/compiler.hpp"

using namespace hoihoi;
using namespace std;

Runtime State::runtime = Runtime();

void State::print_error_location() {
    cerr << "The error from module `" << ((main_module)? "__main__": path.stem().string()) << "`\n";
    cerr << "From line " << get_current_frame().code.get_source_location(get_current_frame().pc).line << endl;
}

ObjectPtr& State::compute_binary_operation(ObjectPtr& valA, const ObjectPtr valB, BinaryOperator operation) {
    switch(operation) {
        case BinaryOperator::PLUS: valA->add(valB); break;
        case BinaryOperator::MINUS: valA->sub(valB); break;
        case BinaryOperator::MUL: valA->mul(valB); break;
        case BinaryOperator::DIV: valA->div(valB); break;
        case BinaryOperator::MODULO: break;

        case BinaryOperator::EQUAL: 
            valA = make_shared<Terminal>(
                Class::terminal_logical, 
                valA->equal(valB)? HOI_TERNARY_HIGH: HOI_TERNARY_LOW
            ); 

        break;
        case BinaryOperator::NOT_EQUAL: 
            valA = make_logical(
                !valA->equal(valB)? HOI_TERNARY_HIGH: HOI_TERNARY_LOW
            );                    
        break;
        case BinaryOperator::OR: valA = valA->or_operation(valB); break;
        case BinaryOperator::AND: valA = valA->and_operation(valB); break;

        case BinaryOperator::LOWER: valA = valA->lower_operation(valB); break;
        case BinaryOperator::GREATER: valA = valA->greater_operation(valB); break;
        case BinaryOperator::EQUIVALENT:  valA = (valA->size() == valA->size())? Terminal::high: Terminal::low;
    }

    return valA;
}

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
                    print_error_location();
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
                    auto class_field = pop();
                    auto name_attribute = pop()->to_string();

                    if(class_field->get_class() == Class::terminal_module) {
                        push(
                            get<ModulePtr>(static_cast<Terminal*>(class_field.get())->get_value())->state->at(name_attribute)
                        );
                    } else {
                        push(class_field->get_class()->get_attribute(name_attribute));
                    }
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    print_error_location();
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
                    print_error_location();
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
                    print_error_location();
                    return 1;
                }

                const auto& val = fun->get_value();

                if(auto* builtin = get_if<shared_ptr<Builtin>>(&val)) {
                    try {
                        if(auto res = builtin->get()->operator()(args)) push(res);
                        break;
                    } catch(exception& e) {
                        cerr << e.what() << "\n";
                        print_error_location();
                        return 1;
                    }
                } else if(auto* bytecode = get_if<shared_ptr<Bytecode>>(&val)) {
                    call_frame(*bytecode->get(), args);
                    get_current_frame().pc--;
                } else {
                    cerr << "Must a cluster function or builtin not a " <<  fun->to_string() << '\n';
                    print_error_location();
                    return 1;
                }
            } break;
            case Opcode::RETURN: this->call_back(); break;
            
            case Opcode::JUMP_ABSOLUTE: get_current_frame().pc += inst.operand; break;
            case Opcode::JUMP_IF_FALSE: if(!pop()->is_high()) get_current_frame().pc += inst.operand; break;

            case Opcode::CONST_INTEGER64_LOWER:
            case Opcode::CONST_INTEGER32: push(make_integer(static_cast<int64_t>(inst.operand))); break;

            case Opcode::CONST_FLOAT_LOWER: {
                push(make_float(bit_cast<double>(static_cast<int64_t>(inst.operand))));
            } break;

            case Opcode::CONST_INTEGER64_HIGHER: {
                auto pop_val = pop();
                auto terminal = static_cast<Terminal*>(pop_val.get());
                auto higher = (static_cast<uint64_t>(inst.operand) << 32UL) | 0x00000000ffffffff;

                terminal->set_value(bit_cast<int64_t>(get<int64_t>(terminal->get_value()) & higher));
                
                push(pop_val);
            } break;

            case Opcode::CONST_FLOAT_HIGHER: {
                auto pop_val = pop();
                auto lower = static_cast<Terminal*>(pop_val.get());
                auto higher = (static_cast<uint64_t>(inst.operand) << 32UL) | 0x00000000ffffffff;

                
                double val = bit_cast<double>(bit_cast<uint64_t>(get<double>(lower->get_value())) & higher);

                lower->set_value(val);
                
                push(pop_val);
            } break;

            case Opcode::CONST_CHAR: push(make_character(static_cast<char>(inst.operand))); break;
            case Opcode::CONST_LOGICAL:
                push(make_logical(static_cast<TernaryLogical>(inst.operand)));
            break;
            case Opcode::CONST_THING: push(
                    (inst.operand)? Terminal::positive_thing: Terminal::negative_thing
                ); 
            break;

        
            case Opcode::BUILD_FUNCTION: push(get_current_frame().code.get_const(inst.operand)); break;

            case Opcode::BUILD_STRING:
            case Opcode::BUILD_VECTOR:
            case Opcode::BUILD_BAG:
            case Opcode::BUILD_SET:
            case Opcode::BUILD_TUPLE:{
                vector<ObjectPtr> val = vector<ObjectPtr>(inst.operand);

                for(int32_t i = 0; i < inst.operand; i++)
                    val[inst.operand - 1 - i] = pop();
                
                if(Opcode::BUILD_STRING == inst.opcode)
                    push(make_shared<String>(move(val)));
                else if(Opcode::BUILD_VECTOR == inst.opcode)
                    push(make_shared<Vector>(move(val)));
                else if(Opcode::BUILD_TUPLE == inst.opcode)
                    push(make_shared<Tuple>(move(val)));
                else if(Opcode::BUILD_BAG == inst.opcode)
                    push(make_shared<Bag>(move(val)));
            }break;

            case Opcode::OPPOSITE: {
                auto val = pop()->copy();
                val->opposite();
                push(val); 
            } break;

            case Opcode::UNARY_OP:{
                try {
                    auto res = pop()->copy();

                    switch(static_cast<UnaryOperator>(inst.operand)) {
                        case UnaryOperator::NOT: 
                            if(res->get_class() == Class::terminal_logical) {
                                res = make_logical(!res->get_logical());
                            } else
                                res->opposite(); 
                        break;
                        case UnaryOperator::OPPOSITE: break;
                    }

                    push(res);
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    print_error_location();
                    return 1;
                }
            }break;

            case Opcode::BINARY_OP:{
                try {
                    auto valB = pop();
                    auto valA = pop()->copy();

                    push(this->compute_binary_operation(valA, valB, static_cast<BinaryOperator>(inst.operand)));
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    print_error_location();
                    return 1;
                }
            }break;

            case Opcode::ASSIGN_BINARY_OP:{
                try {
                    auto valB = pop();
                    auto valA = pop();

                    this->compute_binary_operation(valA, valB, static_cast<BinaryOperator>(inst.operand));
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    print_error_location();
                    return 1;
                }
            }break;

            case Opcode::IMPORT: {
                try {
                    string name_module = pop()->to_string();
                    int res = runtime.load_module(name_module);
                    
                    variables[name_module] = make_module(runtime.get_module(name_module));

                    if(res != 0)
                        return res;
                } catch(exception& e) {
                    cerr << e.what() << "\n";
                    print_error_location();
                    return 1;
                }
            } break;
            
            case Opcode::HALT: return inst.operand;
            default: throw runtime_error("Unknown instruction: " + hoihoi::to_string_opcode(inst.opcode));
        }

        get_current_frame().pc++;
    }

    return 0;
}
