#pragma once

#include <cstdint>
#include <memory>

namespace alba
{

using TypeId = uintptr_t;
static constexpr TypeId EMPTY_TYPE_ID = 0;

namespace detail
{

// generates unique integer type id, as an address of static method
template <class T>
class TypeIdGenerator
{
public:
    static TypeId GetTypeId()
    {
        return reinterpret_cast<TypeId>(std::addressof(GetTypeId));
    }
};

} // namespace details

template <class T>
TypeId GetTypeId()
{
    return detail::TypeIdGenerator<T>::GetTypeId();
}

} // namespace alba
