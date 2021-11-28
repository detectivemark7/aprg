#include "GeometricSeries.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

namespace alba {

namespace algebra {

GeometricSeries::GeometricSeries(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier)
    : SeriesBasedOnFormula(getFormula(firstValue, commonMultiplier), n) {}

GeometricSeries::GeometricSeries(
    AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2, int const nthIndex2)
    : SeriesBasedOnFormula(getFormula(valueAtNthIndex1, nthIndex1, valueAtNthIndex2, nthIndex2), n) {}

Term GeometricSeries::getInfiniteSumStartingFrom(int const startingNthIndex) {
    return getSumStartingAtIndexAndToInfinity(startingNthIndex);
}

Term GeometricSeries::getFormula(AlbaNumber const& firstValue, AlbaNumber const& commonMultiplier) const {
    return Term(firstValue) * (Term(commonMultiplier) ^ Term(n));
}

Term GeometricSeries::getFormula(
    AlbaNumber const& valueAtNthIndex1, int const nthIndex1, AlbaNumber const& valueAtNthIndex2,
    int const nthIndex2) const {
    AlbaNumber commonMultiplier =
        (valueAtNthIndex2 / valueAtNthIndex1) ^ (AlbaNumber(1) / AlbaNumber(nthIndex2 - nthIndex1));
    AlbaNumber firstValue = valueAtNthIndex1 / (commonMultiplier ^ nthIndex1);
    return getFormula(firstValue, commonMultiplier);
}

}  // namespace algebra

}  // namespace alba
