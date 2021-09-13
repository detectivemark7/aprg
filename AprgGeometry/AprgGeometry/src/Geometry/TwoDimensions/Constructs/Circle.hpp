#pragma once

#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <functional>
#include <optional>

namespace alba
{

namespace TwoDimensions
{

class Circle
{
public:
    using TraverseOperation = std::function<void(Point const&)>;
    Circle();
    Circle(Point const& center, double const radius); // (x-center.x)^2 + (y-center.y)^2 = r^2
    Circle(double const a, double const d, double const e, double const f); //ax2+ay2+dx+ey+f=0
    bool operator==(Circle const& circle) const;
    bool operator!=(Circle const& circle) const;
    bool operator<(Circle const& circle) const;
    Point getCenter() const;
    double getRadius() const;
    double getArea() const;
    double getCircumference() const;
    double getEccentricity() const;
    bool isInside(Point const& point) const;
    Points getLocus(double const interval) const;
    void traverseArea(double const interval, TraverseOperation const& traverseOperation) const;
    std::optional<double> calculateYFromX(double const x, double const signOfRoot) const;
    std::optional<double> calculateXFromY(double const y, double const signOfRoot) const;
    std::optional<double> calculateYFromXWithoutCenter(double const x, double const signOfRoot) const;
    std::optional<double> calculateXFromYWithoutCenter(double const y, double const signOfRoot) const;
    Point getPointAtAngle(double const angleInRadians);
    Point getNearestPointInCircumference(Point const& pointNotCircumference) const;

private:
    void determineAndSaveCenterAndRadiusFromCoefficients(double const a, double const d, double const e, double const f);
    Points getPointsInTraversingXAndY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingY(double const signOfX, double const signOfY, double const interval) const;
    Points getPointsInTraversingX(double const signOfX, double const signOfY, double const interval) const;

    friend std::ostream & operator<<(std::ostream & out, Circle const& circle);

    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Circles = std::vector<Circle>;

}
}
