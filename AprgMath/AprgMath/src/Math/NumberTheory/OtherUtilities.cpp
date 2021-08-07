#include "OtherUtilities.hpp"

#include <Algorithm/Search/SumSearch/FourSum.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

using namespace alba::algorithm;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

namespace
{

void findDistinctNonConsecutiveFibonacciNumbersForSum(
        bool & isComplete,
        UnsignedIntegers & fibonaccisForSum,
        UnsignedIntegers const& fibonaccis,
        UnsignedInteger const sum,
        UnsignedInteger const index)
{
    // This can be improved by dynamic programming
    for(UnsignedInteger i=index; i<fibonaccis.size(); i++)
    {
        UnsignedInteger fibonacci(fibonaccis.at(i));
        if(sum > fibonacci)
        {
            fibonaccisForSum.emplace_back(fibonacci);
            findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, sum-fibonacci, index+2);
            if(isComplete)
            {
                break;
            }
            fibonaccisForSum.pop_back();
        }
        else if(sum == fibonacci)
        {
            fibonaccisForSum.emplace_back(fibonacci);
            isComplete = true;
            break;
        }
    }
}

}

bool isLagrangeTheoremTrue(UnsignedInteger const number)
{
    // Lagrange’s theorem states that every positive integer can be represented as a sum of four squares, i.e., a^2 + b^2 + c^2 + d^2.
    // For example, the number 123 can be represented as the sum 8^2 + 5^2 + 5^2 + 3^2.

    UnsignedInteger maxElement = static_cast<UnsignedInteger>(pow(number, 0.5)); // max element is square root
    UnsignedIntegers squaredElements;
    squaredElements.reserve(maxElement-1);
    for(UnsignedInteger i=1; i<maxElement; i++)
    {
        squaredElements.emplace_back(i*i);
    }

    FourSum<UnsignedIntegers> fourSum(squaredElements);
    auto fourValues = fourSum.getPossibleDuplicatedFourValuesWithSum(number);
    UnsignedInteger sumOfSquares = get<0>(fourValues) + get<1>(fourValues) + get<2>(fourValues) + get<3>(fourValues);

    return sumOfSquares == number;
}

bool isZeckendorfTheoremTrue(UnsignedInteger const number)
{
    // Zeckendorf’s theorem states that every positive integer has a unique representation as a sum of Fibonacci numbers
    // such that no two numbers are equal or consecutive Fibonacci numbers.
    // For example, the number 74 can be represented as the sum 55 + 13 + 5 + 1.

    bool result(false);
    UnsignedIntegers fibonaccis(getFibonacciNumbersBelowThisNumber(number));

    bool isComplete(false);
    UnsignedIntegers fibonaccisForSum;
    findDistinctNonConsecutiveFibonacciNumbersForSum(isComplete, fibonaccisForSum, fibonaccis, number, 0);

    if(isComplete)
    {
        UnsignedInteger sumOfFibonaccis = accumulate(fibonaccisForSum.cbegin(), fibonaccisForSum.cend(), 0, std::plus<UnsignedInteger>());
        result = sumOfFibonaccis == number;
    }
    return result;
}

UnsignedInteger getNthFibonacciNumber(UnsignedInteger const number)
{
    // Binets formula:
    double sqrtOf5 = sqrt(5);
    double fibonacciInDouble = (pow(1+sqrtOf5, number)-pow(1-sqrtOf5, number)) / (pow(2, number)*sqrtOf5);
    return getIntegerAfterRoundingADoubleValue<UnsignedInteger>(fibonacciInDouble);
}

UnsignedIntegers getFibonacciNumbersBelowThisNumber(UnsignedInteger const number)
{
    UnsignedIntegers result;
    UnsignedInteger previousPreviousFibonacci(0);
    UnsignedInteger previousFibonacci(0);
    UnsignedInteger currentFibonacci(1);
    while(currentFibonacci < number)
    {
        result.emplace_back(currentFibonacci);
        previousPreviousFibonacci = previousFibonacci;
        previousFibonacci = currentFibonacci;
        currentFibonacci = previousFibonacci + previousPreviousFibonacci;
    }
    return result;
}

}

}
