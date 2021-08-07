#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <Common/Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalEndpoint.hpp>

namespace alba
{

bool isValueInsideTheIntervals(AlbaNumber const innerValue, AlbaNumberIntervals const& outerIntervals);
bool isIntervalInsideTheIntervals(AlbaNumberInterval const& innerInterval, AlbaNumberIntervals const& outerIntervals);
bool areTheIntervalsInsideTheInterval(AlbaNumberIntervals const& innerIntervals, AlbaNumberInterval const& outerInterval);
AlbaNumberIntervalEndpoint::Type getEndpointTypeWithCheckingIfItsClosed(bool const isCloseEndpoint);
AlbaNumberIntervalEndpoint createOpenEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createCloseEndpoint(AlbaNumber const value);
AlbaNumberIntervalEndpoint createEndpoint(
        bool const isCloseEndpoint,
        AlbaNumber const value);
AlbaNumberIntervalEndpoint createPositiveInfinityOpenEndpoint();
AlbaNumberIntervalEndpoint createNegativeInfinityOpenEndpoint();
AlbaNumberInterval createAllRealValuesInterval();

AlbaNumbers getNumbersInsideTheInterval(AlbaNumbers const& numbersToCheck, AlbaNumberInterval const& intervalToCheck);

}
