#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

int main(){
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    l_region.generateSeedPoints(PointGenerator(functions::random_double(0,20), functions::random_double(0,20)), 10, 10);
    std::vector<Point> seeds = l_region.getSeedPoints();

    TriangleVoronoiGenerator g(seeds, l_region);
    Mesh LRandom = g.getMesh();
    LRandom.printInFile("LShapedMesh.txt");
}