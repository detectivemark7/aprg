#pragma once

namespace alba {

namespace algorithm {

template <typename Object>
class BaseStack {
public:
    virtual ~BaseStack() = default;  // virtual destructor because of virtual functions (vtable exists)

    virtual bool isEmpty() const = 0;
    virtual unsigned int getSize() const = 0;
    virtual void push(Object const& object) = 0;
    virtual Object pop() = 0;
};

}  // namespace algorithm

}  // namespace alba
