#pragma once

#include <cstddef>
#include <cstdint>

namespace alba {

template <typename UnderlyingType, std::size_t numberOfBits>
struct AlbaSingleBitField {
    UnderlyingType value : numberOfBits;
};

}  // namespace alba
