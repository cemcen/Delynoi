#ifndef DELYNOI_POLYGONALMESH_H
#define DELYNOI_POLYGONALMESH_H

#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <algorithm>
#include <fstream>
#include <delynoi/models/neighbourhood/EdgeData.h>
#include <delynoi/voronoi/structures/mapdata.h>
#include <unordered_map>
#include <delynoi/models/neighbourhood/Neighbours.h>
#include <delynoi/models/neighbourhood/SegmentMap.h>
#include <delynoi/models/structures/NeighbourInfo.h>
#include <delynoi/models/Mesh.h>
#include "Region.h"
#include <string>

class PolygonalMesh : public Mesh{
protected:
    std::vector<Polygon> polygons;
public:
    PolygonalMesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s, Region r);
    PolygonalMesh(const PolygonalMesh& m);
    PolygonalMesh();
    ~PolygonalMesh();
    void createFromFile(std::string fileName);
    void createFromStream(std::ifstream& ofstream);

    std::vector<Polygon>& getPolygons();
    std::vector<Polygon> getPolygons() const;
    Polygon& getPolygon(int index);
    Polygon getPolygon(int index) const;
    void replacePolygon(int index, Polygon newPolygon);

    void writeElements(std::ofstream& file);
    void update();

    bool areNeighbours(int poly1, int poly2);
    bool areNeighbours(Polygon poly, int poly2);
    bool polygonsTouch(int poly1, int poly2);
    void getNeighboursBySegments(int poly, UniqueList<int> &neighbours);

    int findContainerPolygon(Point p);
    int findContainerPolygon(Point p, int& last);
    int findContainerPolygon(Point p, int init_polygon, int &last);
    int findContainerPolygonLinear(Point p);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet,
                                            std::vector<int> &previousPolygons, int vertexIndex);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, NeighbourInfo& n);

    void getNeighboursByPoint(int poly, UniqueList<int> &neighbours);

};


#endif

