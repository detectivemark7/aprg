#include "SolutionUtilities.hpp"

#include <Algebra/Retrieval/NumbersRetriever.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

AlbaNumber getPositiveLogarithmOfLargestNumber(Term const& term) {
    NumbersRetriever retriever;
    retriever.retrieveFromTerm(term);
    AlbaNumbersSet const& numbers(retriever.getSavedData());
    AlbaNumber initialValue(0);
    if (!numbers.empty()) {
        initialValue = log(getAbsoluteValue((*numbers.cbegin()).getDouble()));
    }
    return initialValue;
}

AlbaNumbers getInitialValuesForIteratingMethods(Term const& term) {
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveInitialValuesForIteratingMethods(allValues, term);
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

void retrieveInitialValuesForIteratingMethods(AlbaNumbersSet& allValues, Term const& term) {
    NumbersRetriever retriever;
    retriever.retrieveFromTerm(term);
    AlbaNumbersSet const& numbers(retriever.getSavedData());
    for (AlbaNumber const& number : numbers) {
        AlbaNumber positiveNumber(getAbsoluteValue(number));
        AlbaNumber positiveLogarithm(log(positiveNumber.getDouble()));
        allValues.emplace(positiveNumber * -1);
        allValues.emplace(positiveLogarithm * -1);
        allValues.emplace(positiveLogarithm);
        allValues.emplace(positiveNumber);
    }
}

AlbaNumbers getInitialValuesForIteratingMethods(Equation const& equation) {
    AlbaNumbers result;
    AlbaNumbersSet allValues;
    retrieveInitialValuesForIteratingMethods(allValues, equation.getLeftHandTerm());
    retrieveInitialValuesForIteratingMethods(allValues, equation.getRightHandTerm());
    result.reserve(allValues.size());
    copy(allValues.cbegin(), allValues.cend(), back_inserter(result));
    return result;
}

}  // namespace algebra

}  // namespace alba
