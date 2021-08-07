#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Geometry/ThreeDimensions/Constructs/Point.hpp>

namespace alba
{

namespace ThreeDimensions
{

class Sphere
{
public:
    Sphere();
    Sphere(Point const& center, double const radius); // (x-center.x)^2 + (y-center.y)^2 + (z-center.z)^2 = r^2
    bool operator==(Sphere const& sphere) const;
    bool operator!=(Sphere const& sphere) const;
    bool operator<(Sphere const& sphere) const;
    Point getCenter() const;
    double getRadius() const;
    bool isInside(Point const& point) const;
    AlbaOptional<double> calculateXFromYAndZ(double const y, double const z, double const signOfRoot) const;
    AlbaOptional<double> calculateYFromXAndZ(double const x, double const z, double const signOfRoot) const;
    AlbaOptional<double> calculateZFromXAndY(double const x, double const y, double const signOfRoot) const;

private:
    friend std::ostream & operator<<(std::ostream & out, Sphere const& sphere);

    Point m_center;
    double m_radius;
    double m_radiusSquared;
};

using Spheres = std::vector<Sphere>;

}
}
