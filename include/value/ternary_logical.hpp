#ifndef HOIHOI_TERNARY_LOGICAL_HPP
#define HOIHOI_TERNARY_LOGICAL_HPP

#include <cstdint>
#include <string>

namespace hoihoi {
    /**
     * \brief Ternay logical just rename the common primitive: low = false, neutral = unknown and high = true
     */
    enum class TernaryLogical: std::uint8_t {
        LOW, NEUTRAL, HIGH
    };

    inline std::string to_string(TernaryLogical a) {
        return (a == TernaryLogical::NEUTRAL)? "neutral":
               (a == TernaryLogical::HIGH)? "high": "low";
    }

    constexpr TernaryLogical operator!(TernaryLogical a) {
        return (a == TernaryLogical::NEUTRAL)? TernaryLogical::NEUTRAL:
               (a == TernaryLogical::HIGH)? TernaryLogical::LOW: TernaryLogical::HIGH;
    }

    constexpr TernaryLogical operator|(TernaryLogical a, TernaryLogical b) { return std::max(a, b); }
    constexpr TernaryLogical& operator|=(TernaryLogical& a, TernaryLogical b) { return a = a | b; }

    constexpr TernaryLogical operator&(TernaryLogical a, TernaryLogical b) { return std::min(a, b); }
    constexpr TernaryLogical& operator&=(TernaryLogical& a, TernaryLogical b) { return a = a & b; }
};

#endif /* HOIHOI_TERNARY_LOGICAL_HPP */
