#include "Line.hpp"

#include <Common/Container/AlbaValueRange.hpp>

#include <algorithm>
#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace ThreeDimensions
{

Line::Line()
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
{}

Line::Line(Point const& first, Point const& second)
    : m_aCoefficient(0)
    , m_bCoefficient(0)
    , m_cCoefficient(0)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
{
    double deltaX = second.getX() - first.getX();
    double deltaY = second.getY() - first.getY();
    double deltaZ = second.getZ() - first.getZ();
    double sign=1;
    vector<double> deltas = {deltaX, deltaY, deltaZ};
    unsigned int negativeNumbers = std::count_if(deltas.cbegin(), deltas.cend(), [&](double const delta)
    {
        return delta<0;
    });
    if(negativeNumbers>1)
    {
        sign=-1;
    }
    m_aCoefficient = deltaX*sign;
    m_bCoefficient = deltaY*sign;
    m_cCoefficient = deltaZ*sign;
    calculateAndSaveInitialValuesIfPossible(first);
}

Line::Line(double const aCoefficient,
           double const bCoefficient,
           double const cCoefficient,
           Point const& point)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_xInitialValue(0)
    , m_yInitialValue(0)
    , m_zInitialValue(0)
{
    calculateAndSaveInitialValuesIfPossible(point);
}

Line::Line(double const aCoefficient,
           double const bCoefficient,
           double const cCoefficient,
           double const xInitialValue,
           double const yInitialValue,
           double const zInitialValue)
    : m_aCoefficient(aCoefficient)
    , m_bCoefficient(bCoefficient)
    , m_cCoefficient(cCoefficient)
    , m_xInitialValue(xInitialValue)
    , m_yInitialValue(yInitialValue)
    , m_zInitialValue(zInitialValue)
{}

bool Line::isInvalid() const
{
    return areAllCoefficientsZero();
}

bool Line::operator==(Line const& line) const
{
    return isAlmostEqual(m_aCoefficient, line.m_aCoefficient)
            && isAlmostEqual(m_bCoefficient, line.m_bCoefficient)
            && isAlmostEqual(m_cCoefficient, line.m_cCoefficient)
            && isAlmostEqual(m_xInitialValue, line.m_xInitialValue)
            && isAlmostEqual(m_yInitialValue, line.m_yInitialValue)
            && isAlmostEqual(m_zInitialValue, line.m_zInitialValue);
}

bool Line::operator!=(Line const& line) const
{
    return !((*this)==line);
}

double Line::getXInitialValue() const
{
    return m_xInitialValue;
}

double Line::getYInitialValue() const
{
    return m_yInitialValue;
}

double Line::getZInitialValue() const
{
    return m_zInitialValue;
}

double Line::getACoefficient() const
{
    return m_aCoefficient;
}

double Line::getBCoefficient() const
{
    return m_bCoefficient;
}

double Line::getCCoefficient() const
{
    return m_cCoefficient;
}

AlbaOptional<double> Line::calculateXFromY(double const y) const
{
    return calculateOtherCoordinate(m_xInitialValue, m_aCoefficient, m_yInitialValue, m_bCoefficient, y);
}

AlbaOptional<double> Line::calculateXFromZ(double const z) const
{
    return calculateOtherCoordinate(m_xInitialValue, m_aCoefficient, m_zInitialValue, m_cCoefficient, z);
}

AlbaOptional<double> Line::calculateYFromX(double const x) const
{
    return calculateOtherCoordinate(m_yInitialValue, m_bCoefficient, m_xInitialValue, m_aCoefficient, x);
}

AlbaOptional<double> Line::calculateYFromZ(double const z) const
{
    return calculateOtherCoordinate(m_yInitialValue, m_bCoefficient, m_zInitialValue, m_cCoefficient, z);
}

AlbaOptional<double> Line::calculateZFromX(double const x) const
{
    return calculateOtherCoordinate(m_zInitialValue, m_cCoefficient, m_xInitialValue, m_aCoefficient, x);
}

AlbaOptional<double> Line::calculateZFromY(double const y) const
{
    return calculateOtherCoordinate(m_zInitialValue, m_cCoefficient, m_yInitialValue, m_bCoefficient, y);
}

void Line::calculateAndSaveInitialValuesIfPossible(Point const& first)
{
    if(!isInvalid())
    {
        double minimizedMultiplierForInitialValue=0;
        if(!isAlmostEqual(m_aCoefficient+m_bCoefficient+m_cCoefficient, 0.0))
        {
            //k is minimizedMultiplierForInitialValue
            //x1+ak + y1+bk + z1+ck = 0
            //-(x1+y1+z1)/(a+b+c) = k
            minimizedMultiplierForInitialValue = -1*(first.getX() + first.getY() + first.getZ())/(m_aCoefficient + m_bCoefficient + m_cCoefficient);
        }
        else
        {
            //x1/a1 = k (so that initial value = 0)
            //get average of all of x and y and z
            unsigned int count=0;
            if(!isAlmostEqual(m_aCoefficient, 0.0))
            {
                minimizedMultiplierForInitialValue += first.getX()/m_aCoefficient;
                count++;
            }
            if(!isAlmostEqual(m_bCoefficient, 0.0))
            {
                minimizedMultiplierForInitialValue += first.getY()/m_bCoefficient;
                count++;
            }
            if(!isAlmostEqual(m_cCoefficient, 0.0))
            {
                minimizedMultiplierForInitialValue += first.getZ()/m_cCoefficient;
                count++;
            }
            minimizedMultiplierForInitialValue = round(-1*minimizedMultiplierForInitialValue/count);
        }
        m_xInitialValue = first.getX() + minimizedMultiplierForInitialValue*m_aCoefficient;
        m_yInitialValue = first.getY() + minimizedMultiplierForInitialValue*m_bCoefficient;
        m_zInitialValue = first.getZ() + minimizedMultiplierForInitialValue*m_cCoefficient;
    }
}

AlbaOptional<double> Line::calculateOtherCoordinate(double const& initialValue1, double const coefficient1, double const& initialValue2, double const coefficient2, double const coordinate2) const
{
    AlbaOptional<double> result;
    if(!isAlmostEqual(coefficient2, 0.0))
    {
        result.setValue( ((coordinate2-initialValue2)/coefficient2*coefficient1) + initialValue1 );
    }
    return result;
}

bool Line::areAllCoefficientsZero() const
{
    return isAlmostEqual(m_aCoefficient, 0.0) && isAlmostEqual(m_cCoefficient, 0.0) && isAlmostEqual(m_cCoefficient, 0.0);
}

ostream & operator<<(ostream & out, Line const& line)
{
    out << "(x-" << line.m_xInitialValue << ")/" << line.m_aCoefficient
        << " = (y-" << line.m_yInitialValue << ")/" << line.m_bCoefficient
        << " = (z-" << line.m_zInitialValue << ")/" << line.m_cCoefficient;
    return out;
}

}
}
