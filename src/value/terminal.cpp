#include "value/value.hpp"

using namespace std;
using namespace hoihoi;

const ObjectPtr Terminal::positive_thing = make_shared<Terminal>(Class::terminal_thing, Thing{}, false);
const ObjectPtr Terminal::negative_thing = make_shared<Terminal>(Class::terminal_thing, Thing{}, true);

const ObjectPtr Terminal::low = make_shared<Terminal>(Class::terminal_logical, TernaryLogical::LOW, true);
const ObjectPtr Terminal::neutral = make_shared<Terminal>(Class::terminal_logical, TernaryLogical::NEUTRAL, false);
const ObjectPtr Terminal::high = make_shared<Terminal>(Class::terminal_logical, TernaryLogical::HIGH, false);

ObjectPtr hoihoi::make_logical(TernaryLogical log) noexcept {
    return (TernaryLogical::NEUTRAL == log)? Terminal::neutral:
            (TernaryLogical::LOW == log)? Terminal::low: Terminal::high;
}
