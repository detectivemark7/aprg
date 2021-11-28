#pragma once

#include <bitset>

namespace alba {

namespace algorithm {

template <typename Input, typename HashValue>
class SignedIntegerBasedHashFunction {
public:
    SignedIntegerBasedHashFunction() = delete;
    ~SignedIntegerBasedHashFunction() = delete;
    SignedIntegerBasedHashFunction(SignedIntegerBasedHashFunction const&) = delete;
    SignedIntegerBasedHashFunction& operator=(SignedIntegerBasedHashFunction const&) = delete;
    SignedIntegerBasedHashFunction(SignedIntegerBasedHashFunction&&) = delete;
    SignedIntegerBasedHashFunction& operator=(SignedIntegerBasedHashFunction&&) = delete;

    static HashValue getHashCode(Input const& input) {
        // note we are including sign bit because its better distributed
        return static_cast<HashValue>(input);
    }

    static HashValue getHash(Input const& input, HashValue const hashSize) { return getHashCode(input) % hashSize; }
};

}  // namespace algorithm

}  // namespace alba
