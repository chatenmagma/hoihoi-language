#ifndef HOIHOI_STATE_HPP
#define HOIHOI_STATE_HPP

#include "value/value.hpp"
#include "bytecode.hpp"

#include "runtime.hpp"

#include <filesystem>

namespace hoihoi {
    struct Frame {
        Bytecode code;
        std::size_t pc;

        std::vector<ObjectPtr> locals;

        Frame(Bytecode code)
            : code(code), pc(0UL) {}
        Frame(Bytecode code, std::vector<ObjectPtr> locals)
            : code(code), pc(0UL), locals(locals) {}
        ~Frame() = default;
    };

    class State {
        private:
            std::unordered_map<std::string, ObjectPtr> variables;

            std::vector<ObjectPtr> stack;
            std::vector<Frame> frames;
            std::size_t limit_frames;
        
            std::filesystem::path path;
            bool main_module;

            ObjectPtr& compute_binary_operation(ObjectPtr& valA, const ObjectPtr valB, BinaryOperator operation);

            void print_error_location();
        public:
            State(bool main_module = true)
                : variables(runtime.get_init_global()), limit_frames(255UL), path(std::filesystem::current_path()), main_module(main_module) {}
            State(std::filesystem::path path, bool main_module = false)
                : variables(runtime.get_init_global()), limit_frames(255UL), path(path), main_module(main_module) {}
            ~State() = default;

            static Runtime runtime;

            inline ObjectPtr& operator[](const std::string& name_global) { return variables.at(name_global); }
            inline const ObjectPtr& operator[](const std::string& name_global) const { return variables.at(name_global); }

            inline ObjectPtr& at(const std::string& name_global) { return variables.at(name_global); }
            inline const ObjectPtr& at(const std::string& name_global) const { return variables.at(name_global); }
            inline void insert(const std::string& name_global, ObjectPtr object) {
                variables.insert_or_assign(name_global, std::move(object));
            }

            inline Frame& get_current_frame() { return frames.back(); }
            inline void call_back() { frames.pop_back(); }
            inline void call_frame(Bytecode code, std::vector<ObjectPtr> locals = {}) {
                if(frames.size() > limit_frames) throw std::runtime_error("Too much frame call");
                frames.emplace_back(code, locals);
                get_current_frame().locals.resize(locals.size() + code.get_nb_local());
            }

            inline void push(ObjectPtr value) { stack.emplace_back(value); }
            inline ObjectPtr pop() {
                if(stack.empty()) throw std::runtime_error("stack underflow");

                auto value = stack.back();
                stack.pop_back();
                return value;
            }

            int execute(const std::string& source_code);
            inline int execute(std::filesystem::path from, const std::string& source_code) {
                this->path = from;
                runtime.set_main_dir(from.parent_path());
                return execute(source_code);
            }
    };
}

#endif /* HOIHOI_STATE_HPP */
