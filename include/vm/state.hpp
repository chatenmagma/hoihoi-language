#ifndef HOIHOI_STATE_HPP
#define HOIHOI_STATE_HPP

#include "value/value.hpp"
#include "bytecode.hpp"

#include "runtime.hpp"

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
            std::vector<ObjectPtr> stack;
            std::vector<Frame> frames;
            std::size_t limit_frames;

            std::unordered_map<std::string, ObjectPtr> variables;
        public:
            State() {
                variables = runtime.get_init_global();
                limit_frames = 255;
            }
            ~State() = default;

            static Runtime runtime;

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
    };
}

#endif /* HOIHOI_STATE_HPP */
