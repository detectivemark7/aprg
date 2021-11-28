#pragma once

#include <Common/Math/Angle/AlbaAngle.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/LineSegment.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <array>

namespace alba {

namespace TwoDimensions {

template <unsigned int numberOfVertices>
class Polygon {
public:
    using Distances = std::array<double, numberOfVertices>;
    Polygon();

    Polygon(std::initializer_list<Point> const& vertices);

    bool isEquilateral() const;
    bool isEquiangular() const;
    bool isRegular() const;

    Lines getLines() const;
    LineSegments getLineSegments() const;
    Points getVertices() const;
    Distances getLengthOfSides() const;
    AlbaAngles getAnglesAtVertices() const;
    AlbaAngle getSumOfAngles() const;

    Points getPoints(double const interval) const;
    void getPointsFromVerticesWithoutLastPoint(
        Points& points, double const interval, unsigned int vertexIndex1, unsigned int vertexIndex2) const;

protected:
    std::array<Point, numberOfVertices> m_vertices;
};

template class Polygon<3>;
template class Polygon<4>;

}  // namespace TwoDimensions
}  // namespace alba
