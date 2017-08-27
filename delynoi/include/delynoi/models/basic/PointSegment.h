#ifndef DELYNOI_POINTSEGMENT_H
#define DELYNOI_POINTSEGMENT_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>

class PointSegment: public Segment<Point>{
public:
    PointSegment(Point p1, Point p2);
    PointSegment();

    double length();
    bool isBoundary(std::vector<Point> p);
    bool contains(Point point);
    bool intersection(PointSegment other, Point& inter);
    std::string getString() const;
    double cartesianAngle();
    bool operator==(const PointSegment other) const;
    bool intersectionInfinite(Point p1, Point p2, Point& inter);
    Pair<double> getSlope();
    bool splitSegment(Point splitPoint, std::vector<PointSegment> &newSegments);
};


#endif 
