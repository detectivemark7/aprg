#include "WrappedTerm.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>

#include <sstream>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

WrappedTerm::WrappedTerm(
        BaseTerm const& baseTerm)
    : baseTermPointer(createBasePointer(baseTerm))
{}

WrappedTerm::WrappedTerm(
        BaseTerm && baseTerm)
    : baseTermPointer(createBasePointer(baseTerm))
{}

WrappedTerm::WrappedTerm(WrappedTerm const& wrappedTerm)
    : baseTermPointer(duplicateUniquePointer(wrappedTerm.baseTermPointer))
{}

WrappedTerm & WrappedTerm::operator=(WrappedTerm const& wrappedTerm)
{
    baseTermPointer = duplicateUniquePointer(wrappedTerm.baseTermPointer);
    return *this;
}

bool WrappedTerm::operator==(WrappedTerm const& second) const
{
    Term const& term1(getTermConstReferenceFromUniquePointer(baseTermPointer));
    Term const& term2(getTermConstReferenceFromUniquePointer(second.baseTermPointer));
    return term1 == term2;
}

bool WrappedTerm::operator!=(WrappedTerm const& second) const
{
    return !(operator==(second));
}

bool WrappedTerm::operator<(WrappedTerm const& second) const
{
    Term const& term1(getTermConstReferenceFromUniquePointer(baseTermPointer));
    Term const& term2(getTermConstReferenceFromUniquePointer(second.baseTermPointer));
    return term1 < term2;
}

void WrappedTerm::clear()
{
    baseTermPointer.reset();
}

ostream & operator<<(ostream & out, WrappedTerm const& wrappedTerm)
{
    out << getTermConstReferenceFromUniquePointer(wrappedTerm.baseTermPointer);
    return out;
}

}

}
