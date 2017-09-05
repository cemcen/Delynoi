#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/hole/CircularHole.h>
#include <delynoi/models/generator/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    Hole circular0 = CircularHole(Point(5,10), 2);
    Hole circular1 = CircularHole(Point(10,5), 2);
    Hole circular2 = CircularHole(Point(5,0), 2);
    Hole circular3 = CircularHole(Point(0,5), 2);
    square.addHole(circular0);
    square.addHole(circular1);
    square.addHole(circular2);
    square.addHole(circular3);

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleVoronoiGenerator generator (seeds, square);
    Mesh m = generator.getMesh();
    m.printInFile("SwissCheeseMesh.txt");

}