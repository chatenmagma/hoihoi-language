#ifndef HOIHOI_TERNARY_LOGICAL_H
#define HOIHOI_TERNARY_LOGICAL_H

#include <stdint.h>

typedef enum hoi_ternary_logical: uint8_t {
    HOI_TERNARY_LOW = 0,
    HOI_TERNARY_NEUTRAL = 1,
    HOI_TERNARY_HIGH = 2
} hoi_ternary_logical_t;

#ifdef __cplusplus
#include <algorithm>
#include <string>

namespace hoihoi {
    using TernaryLogical = hoi_ternary_logical_t;

    inline std::string to_string(TernaryLogical a) {
        return (a == HOI_TERNARY_NEUTRAL)? "neutral":
               (a == HOI_TERNARY_HIGH)? "high": "low";
    }

    constexpr TernaryLogical operator!(TernaryLogical a) {
        return (a == HOI_TERNARY_NEUTRAL)? HOI_TERNARY_NEUTRAL:
               (a == HOI_TERNARY_HIGH)? HOI_TERNARY_LOW: HOI_TERNARY_HIGH;
    }

    constexpr TernaryLogical operator|(TernaryLogical a, TernaryLogical b) { return std::max(a, b); }
    constexpr TernaryLogical& operator|=(TernaryLogical& a, TernaryLogical b) { return a = a | b; }

    constexpr TernaryLogical operator&(TernaryLogical a, TernaryLogical b) { return std::min(a, b); }
    constexpr TernaryLogical& operator&=(TernaryLogical& a, TernaryLogical b) { return a = a & b; }
};

#endif

#endif /* HOIHOI_TERNARY_LOGICAL_H */
