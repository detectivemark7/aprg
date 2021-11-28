#include "Circle.hpp"

#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Helpers/ConstantHelpers.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <cmath>

using namespace alba::mathHelper;
using namespace alba::TwoDimensions::twoDimensionsUtilities;
using namespace std;

namespace alba {

namespace TwoDimensions {

Circle::Circle() : m_center(), m_radius(0), m_radiusSquared(0) {}

Circle::Circle(Point const& center, double const radius)
    : m_center(center), m_radius(radius), m_radiusSquared(radius * radius) {}

Circle::Circle(double const a, double const d, double const e, double const f)
    : m_center(), m_radius(0), m_radiusSquared(0) {
    determineAndSaveCenterAndRadiusFromCoefficients(a, d, e, f);
}

bool Circle::operator==(Circle const& circle) const {
    return (m_center == circle.m_center) && isAlmostEqual(m_radius, circle.m_radius);
}

bool Circle::operator!=(Circle const& circle) const { return !((*this) == circle); }

bool Circle::operator<(Circle const& circle) const {
    bool result(false);
    if (m_center == circle.m_center) {
        return m_radius < circle.m_radius;
    } else {
        return m_center < circle.m_center;
    }
    return result;
}

Point Circle::getCenter() const { return m_center; }

double Circle::getRadius() const { return m_radius; }

double Circle::getArea() const { return getPi() * m_radiusSquared; }

double Circle::getCircumference() const { return getPi() * 2 * m_radius; }

double Circle::getEccentricity() const { return 0; }

bool Circle::isInside(Point const& point) const { return getDistance(m_center, point) <= m_radius; }

Points Circle::getLocus(double const interval) const  // points for circumference
{
    Points result;
    Points pointsInFirstQuarter(getPointsInTraversingXAndY(1, 1, interval));
    Points pointsInSecondQuarter(getPointsInTraversingXAndY(-1, 1, interval));
    Points pointsInThirdQuarter(getPointsInTraversingXAndY(-1, -1, interval));
    Points pointsInFourthQuarter(getPointsInTraversingXAndY(1, -1, interval));
    result.reserve(
        pointsInFirstQuarter.size() + pointsInSecondQuarter.size() + pointsInThirdQuarter.size() +
        pointsInFourthQuarter.size());
    copy(pointsInFirstQuarter.cbegin(), pointsInFirstQuarter.cend() - 1, back_inserter(result));
    copy(pointsInSecondQuarter.cbegin(), pointsInSecondQuarter.cend() - 1, back_inserter(result));
    copy(pointsInThirdQuarter.cbegin(), pointsInThirdQuarter.cend() - 1, back_inserter(result));
    copy(pointsInFourthQuarter.cbegin(), pointsInFourthQuarter.cend() - 1, back_inserter(result));
    return result;
}

void Circle::traverseArea(double const interval, TraverseOperation const& traverseOperation) const {
    for (double y = 0; y <= m_radius; y += interval) {
        auto xAtTheEdgeOfCircleOptional(calculateXFromYWithoutCenter(y, 1));
        if (xAtTheEdgeOfCircleOptional) {
            for (double x = 0; x <= xAtTheEdgeOfCircleOptional.value(); x += interval) {
                if (x == 0 && y == 0) {
                    traverseOperation(m_center);
                } else if (x == 0) {
                    traverseOperation(Point(m_center.getX(), m_center.getY() + y));
                    traverseOperation(Point(m_center.getX(), m_center.getY() - y));
                } else if (y == 0) {
                    traverseOperation(Point(m_center.getX() + x, m_center.getY()));
                    traverseOperation(Point(m_center.getX() - x, m_center.getY()));
                } else {
                    traverseOperation(Point(m_center.getX() + x, m_center.getY() + y));
                    traverseOperation(Point(m_center.getX() - x, m_center.getY() + y));
                    traverseOperation(Point(m_center.getX() + x, m_center.getY() - y));
                    traverseOperation(Point(m_center.getX() - x, m_center.getY() - y));
                }
            }
        }
    }
}

optional<double> Circle::calculateYFromX(double const x, double const signOfRoot) const {
    optional<double> result;
    double discriminant = m_radiusSquared - pow(x - m_center.getX(), 2);
    if (discriminant > 0) {
        result = pow(discriminant, 0.5) * signOfRoot + m_center.getY();
    }
    return result;
}

optional<double> Circle::calculateXFromY(double const y, double const signOfRoot) const {
    optional<double> result;
    double discriminant = m_radiusSquared - pow(y - m_center.getY(), 2);
    if (discriminant > 0) {
        result = pow(discriminant, 0.5) * signOfRoot + m_center.getX();
    }
    return result;
}

optional<double> Circle::calculateYFromXWithoutCenter(double const x, double const signOfRoot) const {
    optional<double> result;
    double discriminant = m_radiusSquared - pow(x, 2);
    if (discriminant > 0) {
        result = pow(discriminant, 0.5) * signOfRoot;
    }
    return result;
}

optional<double> Circle::calculateXFromYWithoutCenter(double const y, double const signOfRoot) const {
    optional<double> result;
    double discriminant = m_radiusSquared - pow(y, 2);
    if (discriminant >= 0) {
        result = pow(discriminant, 0.5) * signOfRoot;
    }
    return result;
}

Point Circle::getPointAtAngle(double const angleInRadians) {
    double deltaX = cos(angleInRadians) * m_radius;
    double deltaY = sin(angleInRadians) * m_radius;
    return Point(m_center.getX() + deltaX, m_center.getY() + deltaY);
}

Point Circle::getNearestPointInCircumference(Point const& point) const {
    Point deltaPoint(point.getX() - m_center.getX(), point.getY() - m_center.getY());
    double angle = atan(deltaPoint.getY() / deltaPoint.getX());
    double nearestDeltaPointX = cos(angle) * m_radius * getSign(deltaPoint.getX());
    double nearestDeltaPointY = sin(angle) * m_radius * getSign(deltaPoint.getY());
    return Point(m_center.getX() + nearestDeltaPointX, m_center.getY() + nearestDeltaPointY);
}

void Circle::determineAndSaveCenterAndRadiusFromCoefficients(
    double const a, double const d, double const e, double const f) {
    double xPart = d / a / 2;
    double yPart = e / a / 2;
    m_center = Point(-xPart, -yPart);
    m_radius = -(f / a) - pow(xPart, 2) - pow(yPart, 2);
    m_radiusSquared = pow(m_radius, 2);
}

Points Circle::getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    Points pointsFromTraversingX(getPointsInTraversingX(signOfX, signOfY, interval));
    Points pointsFromTraversingY(getPointsInTraversingY(signOfX, signOfY, interval));
    if (signOfX > 0 && signOfY > 0) {
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX < 0 && signOfY > 0) {
        result = getMergedPointsInDecreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX < 0 && signOfY < 0) {
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    } else if (signOfX > 0 && signOfY < 0) {
        result = getMergedPointsInIncreasingX(pointsFromTraversingX, pointsFromTraversingY);
    }
    return result;
}

Points Circle::getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    AlbaValueRange<double> yRange(m_center.getY(), m_center.getY() + (m_radius * signOfY), interval);
    yRange.traverse([&](double const yValue) {
        optional<double> xCoordinate = calculateXFromY(yValue, signOfX);
        if (xCoordinate) {
            result.emplace_back(xCoordinate.value(), yValue);
        }
    });
    return result;
}

Points Circle::getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const {
    Points result;
    AlbaValueRange<double> xRange(m_center.getX(), m_center.getX() + (m_radius * signOfX), interval);
    xRange.traverse([&](double const xValue) {
        optional<double> yCoordinate = calculateYFromX(xValue, signOfY);
        if (yCoordinate) {
            result.emplace_back(xValue, yCoordinate.value());
        }
    });
    return result;
}

ostream& operator<<(ostream& out, Circle const& circle) {
    out << "(center: " << circle.m_center << " radius: " << circle.m_radius << ")";
    return out;
}

}  // namespace TwoDimensions
}  // namespace alba
