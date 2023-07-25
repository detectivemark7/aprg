#pragma once

#include <Algorithm/HashFunctions/String/HornerHashFunctionForWholeString.hpp>

#include <string>

namespace alba {

namespace algorithm {

template <typename Index, typename HashValue>
class RabinKarpSubstringSearchWithRunningHash {
public:
    using RadixType = int;
    static constexpr RadixType RADIX = 256;
    static constexpr HashValue A_LARGE_PRIME = 1229952067;  // hard coded for now (think of an implementation later)

    RabinKarpSubstringSearchWithRunningHash(std::string const& query)
        : m_query(query),
          m_queryLength(query.length()),
          m_hornerHashFunction(RADIX, A_LARGE_PRIME),
          m_largeRandomPrime(A_LARGE_PRIME),
          m_radixRaiseToMatchLengthHash(getRadixRaiseToMatchLengthHash()),
          m_queryHash(getHash(m_query)) {}

    Index search(std::string const& searchSpace) const {
        Index result(static_cast<Index>(std::string::npos));
        Index searchLength(searchSpace.length());
        HashValue currentHash(getHash(searchSpace));
        if (m_queryHash == currentHash) {
            result = 0;
        } else {
            for (Index searchIndex = m_queryLength; searchIndex < searchLength; searchIndex++) {
                currentHash =
                    getNextHash(currentHash, searchSpace[searchIndex - m_queryLength], searchSpace[searchIndex]);
                if (m_queryHash == currentHash) {
                    // Monte carlo approach (no double check)
                    result = searchIndex - m_queryLength + 1;
                    break;
                }
            }
        }
        return result;
    }

private:
    HashValue getHash(std::string const& key) const {
        return m_hornerHashFunction.getHashCode(key.substr(0, m_queryLength));
    }

    HashValue getNextHash(HashValue const currentHash, char const charToRemove, char const charToAdd) const {
        // First, subtract value for charToRemove
        HashValue result =
            (currentHash + m_largeRandomPrime - (m_radixRaiseToMatchLengthHash * charToRemove % m_largeRandomPrime)) %
            m_largeRandomPrime;
        // Then, add value for charToAdd
        result = (result * RADIX + charToAdd) % m_largeRandomPrime;
        return result;
    }

    HashValue getRadixRaiseToMatchLengthHash() const {
        HashValue result(1);
        for (int i = 1; i < m_queryLength; i++) {
            result = (result * RADIX) % m_largeRandomPrime;
        }
        return result;
    }

    std::string const m_query;
    Index const m_queryLength;
    HornerHashFunctionForWholeString<HashValue> m_hornerHashFunction;
    HashValue m_largeRandomPrime;
    HashValue m_radixRaiseToMatchLengthHash;
    HashValue m_queryHash;
};

}  // namespace algorithm

}  // namespace alba

// Invented by two Turing award winners Michael Rabin (Turing Award '76) and Dick Karp (Turing Award '85).
// Explained to Sedgewick in 15 seconds -> realized needs to be on the book.

// Basic idea = modular hashing
// -> Compute a hash of patterns character 0 to M-1.
// -> For each i, compute a hash of text characters i to M+i-1.
// -> If pattern hash=text substring hash, check for a match.
// -> It seems like there is a lot of calcuation, but actually there is a simple way to limit the amount of calculation.

// Modular hash function
// -> Using the notation ti for txt.charAt(i) we wish to compute:
// -> xi = (ti*R^(M-1) + t{i+1}*R^(M-1) + ... + t{i+M-1}*R^(0)) mod Q
// Intuition: M-digit, base R integer, modulo Q
// Horner's method: Linear-time method to evaluate a degree-M polynomial -> continuously mod to keep the value low

// Efficiently computing the hash value
// -> We can compute x{i+1} given that we know xi
// -> Key property: Can update the hash function in constant time!
// ---> x{i+1} = (xi - ti*R^(M-1))*R + t{i+M}

// Monte carlo version: return match if has match
// Las vegas version: double check if substring really match, continue to search if false collision

// Theory: If Q is a sufficiently large random prime (about M*N^2), then the probability of a false collision is about
// 1/N. Practice: Choose Q to be a large prime (but not so large to cause overflow). Under reasonable assumptions,
// probability of a collision is about 1/Q

// Monte carlo version:
// -> always runs in linear time
// -> extremely likely to return correct answer (but not always!)

// Las Vegas version:
// -> Always returns correct answer
// -> Extremely unlikely to run in linear time (but worst case is M*N).

// Why bother with this algorithm?
// Advantages:
// -> Extends to 2D patterns.
// -> Extends to finding multiple patterns.
// -> Its easy to extend it to more complicated situations.

// Disadvantages:
// -> For substring search its a little bit slower
// ---> There is an inner loop its kinda long.
// -> Arithmetic ops slower than char compares
// -> Las Vegas version requires backup
// -> Poor worst case guarantee

// How would you extend Rabin-Karp to efficiently search for any one of P possible patterns in text of length N?
