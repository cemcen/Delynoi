#ifndef DELYNOI_RECTANGLE_H
#define DELYNOI_RECTANGLE_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/PointSegment.h>
#include <delynoi/models/Mesh.h>
#include <delynoi/models/polygon/Polygon.h>

class BoundingBox {
private:
    Point p1;
    Point p2;

public:
    BoundingBox(Point p1, Point p2);

    Point getFirst() const;
    Point getSecond() const;

    double getWidth();
    double getHeight();
    double xMin();
    double yMin();
    double xMax();
    double yMax();

    bool operator==(const BoundingBox& other) const;
    bool contains(Point p);
    void getSegments(std::vector<PointSegment>& segments);
};


#endif
