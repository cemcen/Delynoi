#include <delynoi/models/generator/Functor.h>
#include <cmath>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

class CustomGenerator: public Functor{
    inline double apply(double x) {
        return x/2;
    }
};

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    square.generateSeedPoints(PointGenerator(new CustomGenerator(), new CustomGenerator()), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator generator (seeds, square);
    PolygonalMesh m = generator.getMesh();
    m.printInFile("CustomGeneratorMesh.txt");
}