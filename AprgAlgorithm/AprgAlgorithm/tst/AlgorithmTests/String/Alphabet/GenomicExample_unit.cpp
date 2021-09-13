#include <Algorithm/String/Alphabet/Alphabet.hpp>
#include <Common/Bit/AlbaBitField.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>

#include <gtest/gtest.h>

#include <bitset>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{

string compressCharactersToValues(string const& characters)
{
    Alphabet<unsigned char> dnaAlphabet("ACTG");
    stringstream inputSs;
    inputSs << characters;
    stringstream outputSs;
    AlbaStreamBitReader reader(inputSs);
    AlbaStreamBitWriter writer(outputSs);
    while(true)
    {
        bitset<2U> valueBitset(dnaAlphabet.getDigitValue(reader.readCharData()));
        if(!inputSs.eof())
        {
            writer.writeBitsetData<2U>(valueBitset, 0U, 1U);
        }
        else
        {
            break;
        }
    }
    writer.flush();
    return outputSs.str();
}

string expandValuesToCharacters(string const& characters)
{
    Alphabet<unsigned char> dnaAlphabet("ACTG");
    stringstream inputSs;
    inputSs << characters;
    stringstream outputSs;
    AlbaStreamBitReader reader(inputSs);
    AlbaStreamBitWriter writer(outputSs);
    while(true)
    {
        bitset<2U> valueBitset(reader.readBitsetData<2U>(0, 1));
        if(!inputSs.eof())
        {
            writer.writeCharData(dnaAlphabet.getCharacter(static_cast<unsigned char>(valueBitset.to_ulong())));
        }
        else
        {
            break;
        }
    }
    writer.flush();
    return outputSs.str();
}

}

TEST(GenomicExampleTest, CompressCharactersToValuesWorks)
{
    EXPECT_EQ("\x13\x1E\x13", compressCharactersToValues("ATAGATGCATAG"));
}

TEST(GenomicExampleTest, ExpandValuesToCharactersWorks)
{
    EXPECT_EQ("ATAGATGCATAG", expandValuesToCharacters("\x13\x1E\x13"));
}

}

}
