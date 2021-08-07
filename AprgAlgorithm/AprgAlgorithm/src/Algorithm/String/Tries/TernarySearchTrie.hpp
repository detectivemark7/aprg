#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Value>
class TernarySearchTrie : public BaseStringSymbolTable<Value>
{
public:
    using Key = std::string;
    using Keys = stringHelper::strings;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        char c;
        ValueUniquePointer valueUniquePointer;
        NodeUniquePointer left;
        NodeUniquePointer mid;
        NodeUniquePointer right;
    };

    TernarySearchTrie()
        : m_root(nullptr)
    {}

    bool isEmpty() const override
    {
        return getSize() == 0;
    }

    bool doesContain(Key const& key) const override
    {
        Node const*const nodePointer(get(m_root, key, 0));
        return nodePointer != nullptr;
    }

    unsigned int getSize() const override
    {
        return getSize(m_root);
    }

    unsigned int getNumberOfNodes() const
    {
        return getNumberOfNodes(m_root); // dont count the root pointer
    }

    Value get(Key const& key) const override
    {
        Value result{};
        Node const*const nodePointer(get(m_root, key, 0));
        if(nodePointer != nullptr)
        {
            ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
            if(valueUniquePointer)
            {
                result = *valueUniquePointer;
            }
        }
        return result;
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override
    {
        unsigned int longestPrefixLength(getLengthOfLongestPrefix(m_root, keyToCheck, 0U, 0U));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void put(Key const& key, Value const& value) override
    {
        if(!key.empty())
        {
            put(m_root, key, value, 0);
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        deleteBasedOnKey(m_root, key, 0);
    }

    Keys getKeys() const override
    {
        Keys result;
        collectAllKeysAtNode(m_root.get(), std::string(), result);
        return result;
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override
    {
        Keys result;
        Node const*const firstNode(get(m_root, prefix, 0U));
        if(firstNode != nullptr)
        {
            ValueUniquePointer const& valueUniquePointer(firstNode->valueUniquePointer);
            if(valueUniquePointer)
            {
                result.emplace_back(prefix);
            }
            collectAllKeysAtNode(firstNode->mid.get(), prefix, result);
        }
        return result;
    }

    Keys getAllKeysThatMatch(Key const& patternToMatch) const override
    {
        Keys result;
        collectKeysThatMatchAtNode(m_root.get(), std::string(), patternToMatch, result);
        return result;
    }

private:

    unsigned int getSize(NodeUniquePointer const& currentNodePointer) const
    {
        unsigned int result(0);
        if(currentNodePointer)
        {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(valueUniquePointer)
            {
                result++;
            }
            result += getSize(currentNodePointer->left);
            result += getSize(currentNodePointer->right);
            result += getSize(currentNodePointer->mid);
        }
        return result;
    }

    unsigned int getNumberOfNodes(NodeUniquePointer const& currentNodePointer) const
    {
        unsigned int result(0);
        if(currentNodePointer)
        {
            result++;
            result += getNumberOfNodes(currentNodePointer->left);
            result += getNumberOfNodes(currentNodePointer->right);
            result += getNumberOfNodes(currentNodePointer->mid);
        }
        return result;
    }

    Node const* get(
            NodeUniquePointer const& currentNodePointer,
            Key const& key,
            unsigned int const index) const
    {
        Node const* result(nullptr);
        if(currentNodePointer && index<key.length())
        {
            char c(key.at(index));
            if(c < currentNodePointer->c)
            {
                result = get(currentNodePointer->left, key, index); // search left
            }
            else if(c > currentNodePointer->c)
            {
                result = get(currentNodePointer->right, key, index); // search right
            }
            else if(index < key.length() - 1)
            {
                result = get(currentNodePointer->mid, key, index+1); // only advance index when character is a match
            }
            else
            {
                result = currentNodePointer.get();
            }
        }
        return result;
    }

    unsigned int getLengthOfLongestPrefix(
            NodeUniquePointer const& currentNodePointer,
            Key const& keyToCheck,
            unsigned int const index,
            unsigned int const length) const
    {
        unsigned int currentLongestLength(length);
        if(currentNodePointer && index<keyToCheck.length())
        {
            char c(keyToCheck.at(index));
            if(c < currentNodePointer->c)
            {
                currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->left, keyToCheck, index, currentLongestLength);
            }
            else if(c > currentNodePointer->c)
            {
                currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->right, keyToCheck, index, currentLongestLength);
            }
            else if(index < keyToCheck.length())
            {
                if(currentNodePointer->valueUniquePointer)
                {
                    currentLongestLength = index+1;
                }
                currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->mid, keyToCheck, index+1, currentLongestLength);
            }
        }
        return currentLongestLength;
    }

    void collectAllKeysAtNode(
            Node const*const currentNodePointer,
            Key const& previousPrefix,
            Keys & collectedKeys) const
    {
        if(currentNodePointer != nullptr)
        {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            collectAllKeysAtNode(currentNodePointer->left.get(), previousPrefix, collectedKeys);
            Key currentPrefix(previousPrefix + currentNodePointer->c);
            if(valueUniquePointer)
            {
                collectedKeys.emplace_back(currentPrefix);
            }
            collectAllKeysAtNode(currentNodePointer->mid.get(), currentPrefix, collectedKeys);
            collectAllKeysAtNode(currentNodePointer->right.get(), previousPrefix, collectedKeys);
        }
    }

    void collectKeysThatMatchAtNode(
            Node const*const currentNodePointer,
            Key const& previousPrefix,
            Key const& patternToMatch,
            Keys & collectedKeys) const
    {
        if(currentNodePointer != nullptr)
        {
            unsigned int previousPrefixLength = previousPrefix.length();
            unsigned int lastIndexToMatch = patternToMatch.length() - 1;
            char currentChar = currentNodePointer->c;
            char charToMatch = patternToMatch.at(previousPrefixLength);
            Key currentPrefix(previousPrefix + currentNodePointer->c);
            if(charToMatch < currentChar)
            {
                collectKeysThatMatchAtNode(currentNodePointer->left.get(), previousPrefix, patternToMatch, collectedKeys);
            }
            else if(charToMatch == currentChar)
            {
                if(previousPrefixLength < lastIndexToMatch)
                {
                    collectKeysThatMatchAtNode(currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                }
                else if(previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer)
                {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
            else if(charToMatch > currentChar)
            {
                collectKeysThatMatchAtNode(currentNodePointer->right.get(), previousPrefix, patternToMatch, collectedKeys);
            }
            if(charToMatch == '.')
            {
                if(previousPrefixLength < lastIndexToMatch)
                {
                    collectKeysThatMatchAtNode(currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                }
                else if(previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer)
                {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
        }
    }

    void put(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            Value const& value,
            unsigned int const index)
    {
        char charAtKey(key.at(index));
        if(!currentNodePointer)
        {
            currentNodePointer = std::make_unique<Node>(Node{charAtKey, nullptr, nullptr, nullptr, nullptr});
        }
        if(charAtKey < currentNodePointer->c)
        {
            put(currentNodePointer->left, key, value, index);
        }
        else if(charAtKey > currentNodePointer->c)
        {
            put(currentNodePointer->right, key, value, index);
        }
        else if(index < key.length() - 1)
        {
            put(currentNodePointer->mid, key, value, index+1);
        }
        else
        {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        }
    }

    void deleteBasedOnKey(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            unsigned int const index)
    {
        if(currentNodePointer)
        {
            unsigned int lastIndex = key.length() - 1;
            ValueUniquePointer & valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(index < lastIndex)
            {
                char charAtKey(key.at(index));
                if(charAtKey < currentNodePointer->c)
                {
                    deleteBasedOnKey(currentNodePointer->left, key, index);
                }
                else if(charAtKey > currentNodePointer->c)
                {
                    deleteBasedOnKey(currentNodePointer->right, key, index);
                }
                else
                {
                    deleteBasedOnKey(currentNodePointer->mid, key, index+1);
                }
            }
            else if(index == lastIndex)
            {
                valueUniquePointer.reset();
            }
            if(!currentNodePointer->valueUniquePointer && !currentNodePointer->mid)
            {
                if(!currentNodePointer->left && !currentNodePointer->right)
                {
                    currentNodePointer.reset();
                }
                else if(currentNodePointer->left && !currentNodePointer->right)
                {
                    currentNodePointer = std::move(currentNodePointer->left);
                }
                else if(!currentNodePointer->left && currentNodePointer->right)
                {
                    currentNodePointer = std::move(currentNodePointer->right);
                }
                else
                {
                    currentNodePointer->mid = std::move(currentNodePointer->right);
                }
            }
        }
    }

    NodeUniquePointer m_root;
};

// Ternary search tries
// -> Store characters and values in nodes (not keys)
// -> Each node has 3 children: smaller (left), equal (middle), larger (right)
// ---> left: Link to TST for all keys that start with a letter before s
// ---> middle: Link to TST for all keys that start with a letter s
// ---> right: Link to TST for all keys that start with a letter after s

// almost like a binary search tree

// Search in a TST
// -> Follow links corresponding to each character in the key.
// ---> If less, take left link
// ---> if greater, take the right link
// ---> If equal, take the middle link and move to the next key character.
// -> Search hit. Node where search ends has a non-null value.
// -> Search miss. Reach a null link or node where search ends has null value.


}

}
