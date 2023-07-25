#pragma once

#include <vector>

namespace alba {

namespace algorithm {

template <typename Key>
class BaseSet {
public:
    using Keys = std::vector<Key>;

    virtual ~BaseSet() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual bool isEmpty() const = 0;                    // is the set empty
    virtual bool doesContain(Key const& key) const = 0;  // is key exists on set

    virtual int getSize() const = 0;                // get number of keys
    virtual int getRank(Key const& key) const = 0;  // get number of keys less than key

    virtual Key getMinimum() const = 0;                // get smallest key
    virtual Key getMaximum() const = 0;                // get largest key
    virtual Key selectAt(int const rank) const = 0;    // get key at rank
    virtual Key getFloor(Key const& key) const = 0;    // get largest key less than or equal to key
    virtual Key getCeiling(Key const& key) const = 0;  // get smallest key greater than or equal to key

    virtual void put(Key const& key) = 0;               // put key
    virtual void deleteBasedOnKey(Key const& key) = 0;  // remove key from the set
    virtual void deleteMinimum() = 0;                   // remove smallest key from the set
    virtual void deleteMaximum() = 0;                   // remove largest key from the set

    virtual Keys getKeys() const = 0;  // get all keys in sorted order
    virtual Keys getKeysInRangeInclusive(
        Key const& low, Key const& high) const = 0;  // get all keys that fall in range in sorted order
};

}  // namespace algorithm

}  // namespace alba
