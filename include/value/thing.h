#ifndef HOIHOI_THING_H
#define HOIHOI_THING_H

#ifdef __cplusplus
#include <string>

namespace hoihoi {
#endif

typedef struct hoi_thing {
    bool negative;

#ifdef __cplusplus
    explicit hoi_thing()
        : negative(false) {}
    explicit hoi_thing(bool negative)
        : negative(negative) {}
#endif

} hoi_thing_t;

#ifdef __cplusplus
using Thing = hoi_thing_t;

inline std::string to_string(Thing thing) {
    return thing.negative? "-thing": "thing";
}

}
#endif

#endif /* HOIHOI_THING_H */