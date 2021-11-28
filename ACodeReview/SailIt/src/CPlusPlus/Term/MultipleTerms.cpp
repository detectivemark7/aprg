#include "MultipleTerms.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

namespace codeReview {

MultipleTerms::MultipleTerms(initializer_list<Term> const& initializerList)
    : m_terms(initializerList.begin(), initializerList.end()) {}

bool MultipleTerms::isEqualToAnyOfTheTerms(Term const& termToCompare) const {
    return any_of(m_terms.begin(), m_terms.end(), [termToCompare](Term term) { return term == termToCompare; });
}

}  // namespace codeReview
