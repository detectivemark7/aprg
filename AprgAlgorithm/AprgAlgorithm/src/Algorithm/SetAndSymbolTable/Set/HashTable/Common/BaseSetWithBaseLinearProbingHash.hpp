#pragma once

namespace alba {

namespace algorithm {

template <typename BaseLinearProbingHash>
class BaseSetWithBaseLinearProbingHash : public BaseLinearProbingHash {
public:
    using Key = typename BaseLinearProbingHash::Key;
    using Entry = typename BaseLinearProbingHash::Entry;
    using EntryUniquePointer = typename BaseLinearProbingHash::EntryUniquePointer;
    using EntryPointers = typename BaseLinearProbingHash::EntryPointers;

    BaseSetWithBaseLinearProbingHash()
        : b_size(BaseLinearProbingHash::m_size), b_entryPointers(BaseLinearProbingHash::m_entryPointers) {}

    ~BaseSetWithBaseLinearProbingHash() override = default;  // no need for virtual destructor because base destructor
                                                             // is virtual (similar to other virtual functions)

    void put(Key const& key) override  // overrides in BaseSet
    {
        this->resizeOnPutIfNeeded();
        bool isFound(false);
        unsigned int i = this->getHash(key);
        for (; b_entryPointers[i]; this->incrementHashTableIndexWithWrapAround(i)) {
            EntryUniquePointer& entryPointer(b_entryPointers[i]);
            if (key == entryPointer->key) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            b_entryPointers[i].reset(new Entry{key});
        }
        b_size++;
    }

protected:
    void putEntry(Entry const& entry) override  // overrides in BaseLinearProbingHash
    {
        put(entry.key);
    }

private:
    unsigned int& b_size;
    EntryPointers& b_entryPointers;
};

}  // namespace algorithm

}  // namespace alba
