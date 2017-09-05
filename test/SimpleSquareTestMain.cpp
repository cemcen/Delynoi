#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/models/generator/noise/noise.h>

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(functions::displace_points(1), functions::displace_points(0.5)), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();
    TriangleVoronoiGenerator g(seeds, square);
    Mesh m = g.getMesh();
    Mesh t = g.getDelaunay();
    m.printInFile("simpleSquareMesh.txt");
    t.printInFile("simpleSquareMesh_t.txt");
}