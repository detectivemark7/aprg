#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/SolutionSet.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

namespace DomainAndRange
{

using FunctionToCheck=std::function<AlbaNumber(AlbaNumber const&)>;

SolutionSet calculateDomainUsingTransitionValues(
        AlbaNumbers const& domainValuesToCheck,
        FunctionToCheck const& functionToCheck);
SolutionSet calculateDomainForTermWithOneVariable(
        AlbaNumbers const& valuesToCheck,
        Term const& term);
SolutionSet calculateDomainForTermWithOneVariable(
        Term const& term);

SolutionSet calculateDomainForEquation(
        std::string const& variableNameToCheck,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation);
SolutionSet calculateDomainForEquation(
        std::string const& variableNameToCheck,
        Equation const& equation);

SolutionSet calculateRangeForEquation(
        std::string const& variableNameToCheck,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation);
SolutionSet calculateRangeForEquation(
        std::string const& variableNameToCheck,
        Equation const& equation);

SolutionSet calculateDomainForEquationWithVariableToSubstitute(
        std::string const& variableNameToSubstitute,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation);

void collectAndUniqueValuesAndSort(
        AlbaNumbersSet & sortedValues,
        AlbaNumbers const& valuesToCheck);
void collectMinAndMaxValues(
        AlbaNumbersSet & collectedValues,
        AlbaNumbersSet const& sortedValues);
void appendTransitionValues(
        AlbaNumbersSet & transitionValues,
        AlbaNumbersSet const& sortedValues,
        FunctionToCheck const& functionToCheck);
AlbaNumbers getNumbers(AlbaNumbersSet const& collectedValues);

AlbaNumber getTransitionValue(
        AlbaNumber const& inputValueYieldsToFiniteValue,
        AlbaNumber const& inputValueYieldsToNonFiniteValue,
        DomainAndRange::FunctionToCheck const& functionToCheck);

void retrieveTwoVariableNames(
        std::string & nameThatMatch,
        std::string & nameThatDoesNotMatch,
        VariableNamesSet const& variableNames,
        std::string const& variableNameToCheck);

bool isOneToOne(
        std::string const& variableNameToCheck,
        Equation const& equation);


}

}

}
