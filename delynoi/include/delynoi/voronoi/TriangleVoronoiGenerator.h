#ifndef DELYNOI_TRIANGLEMESHGENERATOR_H
#define DELYNOI_TRIANGLEMESHGENERATOR_H

#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/PolygonalMesh.h>

class TriangleVoronoiGenerator {
private:
    PolygonalMesh mesh;
public:
    TriangleVoronoiGenerator(std::vector<Point>& point_list, Region region);
    PolygonalMesh getMesh();
};

#endif
