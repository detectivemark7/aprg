#include "Utilities.hpp"

#include <AudioManipulator/AudioManipulator.hpp>
#include <AudioManipulator/NearestSamples.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <algorithm>
#include <numeric>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace AprgAudio
{

void retrieveDeltas(
        Samples & deltaSamples,
        Samples const& pointerOfSampleToCheck,
        unsigned int const numberOfSamples)
{
    deltaSamples.reserve(numberOfSamples);
    double previousValue(0);
    for(unsigned int i=0; i<numberOfSamples; i++)
    {
        deltaSamples.emplace_back(pointerOfSampleToCheck[i]-previousValue);
        previousValue=pointerOfSampleToCheck[i];
    }
}

double getSumInRange(
        Samples const& samples,
        unsigned int const startIndexIncluded,
        unsigned int const endIndexExcluded)
{
    return accumulate(samples.cbegin()+startIndexIncluded, samples.cbegin()+endIndexExcluded, 0.0);
}

double getAverageOfSamples(Samples const& samples)
{
    return accumulate(samples.cbegin(), samples.cend(), 0.0) / samples.size();
}

double getAverageInRange(
        Samples const& samples,
        unsigned int const startIndexIncluded,
        unsigned int const endIndexExcluded)
{
    return accumulate(samples.cbegin()+startIndexIncluded, samples.cbegin()+endIndexExcluded, 0.0) / samples.size();
}

double getCommonMultiplierForDeltaSamples(
        Samples const& samples,
        unsigned int const startIndexIncluded,
        unsigned int const endIndexExcluded)
{
    double multiplier=getAverageInRange(samples, startIndexIncluded, endIndexExcluded);
    if(isAlmostEqual(multiplier, 0.0))
    {
        multiplier=1;
    }
    return multiplier;
}

double getCommonMultiplierUsingSumAndNumberOfItems(
        double const sum,
        unsigned int const numberOfItems)
{
    double multiplier=sum/numberOfItems;
    if(isAlmostEqual(multiplier, 0.0))
    {
        multiplier=1;
    }
    return multiplier;
}

void multiplyValueToAllSamples(
        Samples & samples,
        double const value)
{
    for(double & sample : samples)
    {
        sample*=value;
    }
}

DoubleOptional compareDeltasAndGetDifference(
        Samples const& deltaSamples1,
        Samples const& deltaSamples2,
        double const multiplierToSample2,
        unsigned int const startOfDeltaSamples1,
        unsigned int const startOfDeltaSamples2,
        unsigned int const numberOfSamples)
{
    constexpr double limitOfOneDifference=2;
    DoubleOptional result;
    double currentValue1(0);
    double currentValue2(0);
    double totalDifference(0);
    bool hasLimitExceeded(false);

    for(unsigned int i=0; i<numberOfSamples; i+=1)
    {
        double deltaSample1 = deltaSamples1[startOfDeltaSamples1+i];
        double deltaSample2 = deltaSamples2[startOfDeltaSamples2+i];
        currentValue1+=deltaSample1;
        currentValue2+=(deltaSample2*multiplierToSample2);
        double currentPositiveDifference=getAbsoluteValue(currentValue1-currentValue2);
        if(limitOfOneDifference<currentPositiveDifference)
        {
            hasLimitExceeded=true;
            break;
        }
        totalDifference+=currentPositiveDifference;
    }
    if(!hasLimitExceeded)
    {
        result.setValue(totalDifference/numberOfSamples);
    }
    return result;
}

void searchForBestSampleIndexes(
        SearchResultsDetails & replicateAndSearchIndexes,
        unsigned int const sampleIntervalForReplication,
        unsigned int const numberOfSamplesForReplication,
        unsigned int const numberOfSearchSamplesPerReplication,
        Samples const& samplesToReplicate,
        Samples const& samplesToSearch)
{
    Samples deltaSamplesToReplicate;
    retrieveDeltas(deltaSamplesToReplicate, samplesToReplicate, samplesToReplicate.size());

    Samples deltaSamplesToSearch;
    retrieveDeltas(deltaSamplesToSearch, samplesToSearch, samplesToSearch.size());

    NearestSamples nearestSamplesToSearch(samplesToSearch);

    for(unsigned int replicationIndex=0; replicationIndex<deltaSamplesToReplicate.size(); replicationIndex+=sampleIntervalForReplication)
    {
        unsigned int numberOfSamplesToCompare = min(numberOfSamplesForReplication, static_cast<unsigned int>(deltaSamplesToReplicate.size()-replicationIndex));
        double commonMultiplierInReplicate = getCommonMultiplierForDeltaSamples(
                    deltaSamplesToReplicate, replicationIndex, replicationIndex+numberOfSamplesToCompare);
        Indexes searchIndexes(nearestSamplesToSearch.getNearestSamplesIndexes(samplesToReplicate[replicationIndex], numberOfSearchSamplesPerReplication));
        bool isFirst(true);
        SearchResultDetails searchResult{false, replicationIndex, 0, 0, 0.0, 0.0};
        for(unsigned int searchIndex : searchIndexes)
        {
            unsigned lastExcludedIndex=searchIndex+numberOfSamplesToCompare;
            if(lastExcludedIndex<=deltaSamplesToSearch.size())
            {
                double commonMultiplierInSearch = getCommonMultiplierForDeltaSamples(
                            deltaSamplesToSearch, searchIndex, lastExcludedIndex);
                double multiplierForSearch = commonMultiplierInReplicate/commonMultiplierInSearch;
                DoubleOptional differenceOptional = compareDeltasAndGetDifference(
                            deltaSamplesToReplicate, deltaSamplesToSearch,
                            multiplierForSearch,
                            replicationIndex, searchIndex,
                            numberOfSamplesToCompare);
                if(differenceOptional.hasContent())
                {
                    if(isFirst || searchResult.minDifference > differenceOptional.get())
                    {
                        searchResult.isSampleFound=true;
                        searchResult.searchIndex=searchIndex;
                        searchResult.numberOfSamples=numberOfSamplesToCompare;
                        searchResult.multiplierForSearch=multiplierForSearch;
                        searchResult.minDifference=differenceOptional.get();
                        isFirst=false;
                    }
                }
            }
        }
        replicateAndSearchIndexes.emplace_back(searchResult);
    }
}

void searchAndTryToReplicateSamples(
        AudioInDouble & audioToChange,
        AudioInDouble const& audioToReplicate,
        AudioInDouble const& audioToSearch,
        unsigned channelIndexInAudioToChange,
        unsigned channelIndexInAudioToReplicate,
        unsigned channelIndexInAudioToSearch,
        bool const alwaysPutNewValue)
{
    SearchResultsDetails replicateAndSearchIndexes;
    Samples const& samplesToReplicate(audioToReplicate.getSamplesAtChannel(channelIndexInAudioToReplicate));
    Samples const& samplesToSearch(audioToSearch.getSamplesAtChannel(channelIndexInAudioToSearch));
    searchForBestSampleIndexes(replicateAndSearchIndexes, 24000, 48000, 100, samplesToReplicate, samplesToSearch);

    Samples & samplesToChange(audioToChange.getSamplesReferenceAtChannel(channelIndexInAudioToChange));
    NewSamplesBuilder newSamplesBuilder(samplesToReplicate);
    newSamplesBuilder.putSamplesBasedOnSearchResultAndSamples(samplesToChange, replicateAndSearchIndexes, samplesToSearch, alwaysPutNewValue);
}

void searchAndTryToReplicate(
        std::string const& filePathForAudioToChange,
        std::string const& filePathForAudioToReplicate,
        std::string const& filePathForAudioToSearch,
        bool const alwaysPutNewValue)
{
    AudioManipulator audioToReplicateManipulator(filePathForAudioToReplicate);
    AudioManipulator audioToSearchManipulator(filePathForAudioToSearch);
    AudioManipulator audioToChangeManipulator(filePathForAudioToChange);
    AudioInDouble const& audioToReplicate(audioToReplicateManipulator.getAudio());
    AudioInDouble const& audioToSearch(audioToSearchManipulator.getAudio());
    AudioInDouble & audioToChange(audioToChangeManipulator.getAudioReference());

    unsigned int numberOfChannels = max(max(audioToReplicate.getNumChannels(), audioToSearch.getNumChannels()), audioToChange.getNumChannels());
    for(unsigned int i=0; i<numberOfChannels; i++)
    {
        searchAndTryToReplicateSamples(
                    audioToChange, audioToReplicate, audioToSearch,
                    clampHigherBound(i, audioToChange.getNumChannels()),
                    clampHigherBound(i, audioToReplicate.getNumChannels()),
                    clampHigherBound(i, audioToSearch.getNumChannels()),
                    alwaysPutNewValue);
    }
    audioToChangeManipulator.saveAudioIntoCurrentFile();

}


}

}
