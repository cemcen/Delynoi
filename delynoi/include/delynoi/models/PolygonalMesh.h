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
    PolygonalMesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s);
    PolygonalMesh(const PolygonalMesh& m);
    PolygonalMesh();
    void createFromFile(std::string fileName);
    void createFromStream(std::ifstream& ofstream);

    std::vector<Polygon>& getPolygons();
    std::vector<Polygon> getPolygons() const;
    Polygon& getPolygon(int index);

    void writeElements(std::ofstream& file);
};


#endif

