#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/models/generator/noise/noise.h>
#include <chrono>

int main(){
    std::vector<int> numberOfPoints = {2,3,5,6,10,12,15,20,25,30,35,40,45,50,55};

    std::string path = utilities::getPath();
    path += "time_results.txt";

    std::ofstream file;
    file.open(path, std::ios::out);

    for (int i = 0; i < numberOfPoints.size(); ++i) {
        std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
        Region square(square_points);

        square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), numberOfPoints[i], numberOfPoints[i]);
        std::vector<Point> seeds = square.getSeedPoints();

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        TriangleVoronoiGenerator g(seeds, square);
        Mesh<Polygon> m = g.getMesh();
        Mesh<Polygon> t = g.getTriangulation();

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        std::cout << duration << ",";

        file << "Numero de puntos: " << numberOfPoints[i]*numberOfPoints[i] << " Tiempo: " << duration << std::endl;

        std::string fileName = "mesh_";
        fileName += utilities::toString(i) + ".txt";

        std::string trianglefileName = "triangle_";
        trianglefileName += utilities::toString(i) + ".txt";

        t.printInFile(trianglefileName);
    }

    return 0;
}