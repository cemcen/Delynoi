#ifndef DELYNOI_SEGMENTMAP_H
#define DELYNOI_SEGMENTMAP_H

#include <delynoi/voronoi/structures/mapdata.h>
#include <utilities/Pair.h>
#include <unordered_map>
#include "Neighbours.h"
#include <fstream>
#include <delynoi/models/basic/IndexSegment.h>

struct NeighboursHasher{
    std::size_t operator()(const Neighbours &k) const {
        return utilities::hash32(k.getFirst()) + utilities::hash32(k.getSecond());
    }
};

class SegmentMap{
private:
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher> map;
public:
    SegmentMap();
    void insert(IndexSegment s, int polygonIndex);
    void insert(IndexSegment s, Neighbours n);
    Neighbours& get(IndexSegment s);
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher>& getMap();
    int size();
    void delete_element(IndexSegment key);
    void printInFile(std::string fileName);
    bool containsSegment(IndexSegment s);

};

#endif 
