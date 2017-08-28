#ifndef DELYNOI_MESH_H
#define DELYNOI_MESH_H

#include <delynoi/models/neighbourhood/SegmentMap.h>
#include <utilities/UniqueList.h>
#include <fstream>

class Mesh{
protected:
    SegmentMap edges;
    UniqueList<Point> points;
public:
    void printInStream(std::ofstream& file);
    virtual void printInFile(std::string fileName);
    virtual void writeElements(std::ofstream& file) = 0;

    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    UniqueList<Point>& getPoints();
    UniqueList<Point> getPoints() const;

    bool isFull();

    Point getPoint(int i);
    Neighbours getNeighbours(IndexSegment s);
};


#endif