#ifndef DELYNOI_DELAUNAYTOVORONOI_H
#define DELYNOI_DELAUNAYTOVORONOI_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Triangle.h>
#include <delynoi/voronoi/structures/DelaunayInfo.h>
#include <delynoi/models/PolygonalMesh.h>

class DelaunayToVoronoi {
private:
    PolygonalMesh mesh;

    Point getCircumcenter(DelaunayInfo del, int triangle, int edge);
public:
    explicit DelaunayToVoronoi(DelaunayInfo del);
    PolygonalMesh getMesh();
};

#endif