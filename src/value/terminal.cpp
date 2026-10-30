#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

const ObjectPtr Terminal::positive_thing = make_shared<Terminal>(Class::terminal_thing, Thing(), false);
const ObjectPtr Terminal::negative_thing = make_shared<Terminal>(Class::terminal_thing, Thing(false), true);

const ObjectPtr Terminal::low = make_shared<Terminal>(Class::terminal_logical, HOI_TERNARY_LOW, true);
const ObjectPtr Terminal::neutral = make_shared<Terminal>(Class::terminal_logical, HOI_TERNARY_NEUTRAL, false);
const ObjectPtr Terminal::high = make_shared<Terminal>(Class::terminal_logical, HOI_TERNARY_HIGH, false);

ObjectPtr hoihoi::make_logical(TernaryLogical log) noexcept {
    return (HOI_TERNARY_NEUTRAL == log)? Terminal::neutral:
            (HOI_TERNARY_HIGH == log)? Terminal::low: Terminal::high;
}
