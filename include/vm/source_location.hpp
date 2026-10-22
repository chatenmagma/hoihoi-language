#pragma once

#include <cstddef>

namespace hoihoi {
    struct SourceLocation {
        std::size_t line;
        std::size_t column;

        SourceLocation()
            : line(0UL), column(0UL) {}
        SourceLocation(std::size_t line, std::size_t column)
            : line(line), column(column) {}
        ~SourceLocation() = default;
    };
}
