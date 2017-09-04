#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/voronoi/DelaunayToVoronoi.h>


TriangleVoronoiGenerator::TriangleVoronoiGenerator(std::vector<Point> &point_list, Region region) {
    DelaunayInfo delaunay = TriangleDelaunayGenerator(region, point_list).getDelaunay();
    this->mesh = DelaunayToVoronoi(delaunay).getMesh();
}

PolygonalMesh TriangleVoronoiGenerator::getMesh() {
    return this->mesh;
}

