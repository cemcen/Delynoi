#ifndef DELYNOI_MESHGENERATOR_H
#define DELYNOI_MESHGENERATOR_H

#include <delynoi/models/PolygonalMesh.h>

class MeshGenerator {
public:
    virtual PolygonalMesh getMesh() = 0;
};


#endif
