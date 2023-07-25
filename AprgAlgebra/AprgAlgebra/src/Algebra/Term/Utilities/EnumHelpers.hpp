#pragma once

#include <Algebra/Term/TermTypes/OperatorLevel.hpp>
#include <Algebra/Term/TermTypes/TermAssociationType.hpp>
#include <Algebra/Term/TermTypes/TermType.hpp>

#include <string>

namespace alba {

namespace algebra {
int getAssociationPriority(TermAssociationType const association);
int getOperatorLevelInversePriority(OperatorLevel const operatorLevel);
int getTermTypePriorityValue(TermType const termType);

TermAssociationType getReversedAssociationType(TermAssociationType const associationType);

std::string getEnumShortString(TermType const termType);
std::string getEnumShortString(TermAssociationType const association);
std::string getEnumShortString(OperatorLevel const operatorLevel);

}  // namespace algebra

}  // namespace alba
