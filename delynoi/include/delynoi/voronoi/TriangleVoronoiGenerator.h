#ifndef DELYNOI_TRIANGLEMESHGENERATOR_H
#define DELYNOI_TRIANGLEMESHGENERATOR_H

#include <delynoi/voronoi/TriangleDelaunayGenerator.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/Mesh.h>

class TriangleVoronoiGenerator {
private:
    Mesh voronoi;
    Mesh delaunay;
public:
    TriangleVoronoiGenerator(std::vector<Point>& point_list, Region region);
    Mesh getMesh();
    Mesh getDelaunay();
};

#endif
