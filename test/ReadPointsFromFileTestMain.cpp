#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(square_points);

    square.addSeedsFromFile("points_file.txt");
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleVoronoiGenerator generator (seeds, square);
    Mesh<Polygon> m = generator.getMesh();
    m.printInFile("ReadFromFileMesh.txt");



}