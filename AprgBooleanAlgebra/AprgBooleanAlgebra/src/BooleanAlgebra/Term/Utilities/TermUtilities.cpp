#include "TermUtilities.hpp"

#include <BooleanAlgebra/Retrieval/VariableNamesRetriever.hpp>
#include <BooleanAlgebra/Term/Operators/TermOperators.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

bool isNonEmptyOrNonOperatorType(Term const& term) {
    TermType termType(term.getTermType());
    return TermType::Empty != termType && TermType::Operator != termType;
}

bool isNonEmptyOrNonOperatorOrNonExpressionType(Term const& term) {
    TermType termType(term.getTermType());
    return TermType::Empty != termType && TermType::Operator != termType && TermType::Expression != termType;
}

bool getNoEffectValueInOperation(OperatorLevel const operatorLevel) {
    return OperatorLevel::And == operatorLevel ? true : OperatorLevel::Or == operatorLevel ? false : false;
}

bool getShortCircuitValueEffectInOperation(OperatorLevel const operatorLevel) {
    return OperatorLevel::And == operatorLevel ? false : OperatorLevel::Or == operatorLevel ? true : false;
}

VariableNamesSet getVariableNames(Term const& term) {
    VariableNamesRetriever retriever;
    retriever.retrieveFromTerm(term);
    return retriever.getSavedData();
}

Term getTermFromVariableAndPrimeValue(string const& variableName, char const primeValue) {
    Term result;
    if ('0' == primeValue) {
        result = Term(VariableTerm::createNegatedVariableTerm(variableName));
    } else if ('1' == primeValue) {
        result = Term(variableName);
    }
    return result;
}

}  // namespace booleanAlgebra

}  // namespace alba
