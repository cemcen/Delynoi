#include <string>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>
#include <delynoi/models/hole/CircularHole.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/models/generator/noise/noise.h>

void generateTest_Polygon(std::string testName, Region r, std::vector<Point> points){
    TriangleVoronoiGenerator g(points, r);

    Mesh<Polygon> m = g.getMesh();
    m.printInFile(testName + ".txt");
}

void generateTest_Triangle(std::string testName, Region r, std::vector<Point> points){
    TriangleDelaunayGenerator g(r,points);

    Mesh<Triangle> m = g.getConformingDelaunayTriangulation();
    m.printInFile(testName + "_triangle.txt");
}

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    std::vector<Point> romboid_points = {Point(0,0), Point(10,0), Point(15,10), Point(5,10)};
    Region romboid(romboid_points);

    std::vector<Point> quarter_circle_points = {Point(0,0), Point(10,0), Point(10,10)};
    std::vector<Point> quarter = delynoi_utilities::generateArcPoints(Point(10,0), 10, 90.0, 180.0);
    quarter_circle_points.insert(quarter_circle_points.end(), quarter.begin(), quarter.end());

    Region quarter_circle(quarter_circle_points);

    std::vector<Point> unicorn_points = {Point(2,0), Point(3,0.5), Point(3.5,2), Point(4,4), Point(6,4), Point(8.5,4),
                                         Point(9,2), Point(9.5,0.5), Point(10,0), Point(10.5,0.5), Point(11.2,2.5),
                                         Point(11.5,4.5), Point(11.8,8.75), Point(11.8,11.5), Point(13.5,11), Point(14.5,11.2),
                                         Point(15,12), Point(15,13), Point(15,14.5), Point(14,16.5), Point(15,19.5), Point(15.2,20),
                                         Point(14.5,19.7), Point(11.8,18.2), Point(10.5,18.3), Point(10,18), Point(8,16),
                                         Point(7.3,15.3), Point(7,13.8), Point(6.7,11.5), Point(3.3,11.3), Point(1,10.5),
                                         Point(0.4,8.8), Point(0.3,6.8), Point(0.4,4), Point(0.8,2.1), Point(1.3,0.4)};
    Region unicorn(unicorn_points);

    /*----------------Random generation--------------------------------------------------------------------*/
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest_Polygon("squareRandom5", square, square.getSeedPoints());
    generateTest_Triangle("squareRandom5", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,10),0,1),
                                             noise::random_double_noise(functions::random_double(0,10),0,1)), 5, 5);
    generateTest_Polygon("squareRandomNoise5", square, square.getSeedPoints());
    generateTest_Triangle("squareRandomNoise5", square, square.getSeedPoints());
    square.cleanSeedPoints();


    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("squareRandom10", square, square.getSeedPoints());
    generateTest_Triangle("squareRandom10", square, square.getSeedPoints());
    square.printInFile("square.txt");
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 10, 10);
    generateTest_Polygon("squareConstantAlternating10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constantAlternating(),0,1),
                                             noise::random_double_noise(functions::constant(),0,1)), 10, 10);
    generateTest_Polygon("squareConstantAlternating10Noise", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::sine(2,10,0), functions::independent_variable::x), 10, 10);
    generateTest_Polygon("squareSine", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::sine(4,10,0),0,1),
                                             functions::independent_variable::x), 10, 10);
    generateTest_Polygon("squareSineNoise", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,10),0,1),
                                             noise::random_double_noise(functions::random_double(0,10),0,1)), 10, 10);
    generateTest_Polygon("squareRandomNoise10", square, square.getSeedPoints());
    generateTest_Triangle("squareRandomNoise10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 5, 5);
    generateTest_Polygon("romboidRandom5", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidRandom5", romboid, romboid.getSeedPoints());
    romboid.printInFile("romboid.txt");
    romboid.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,15),0,1),
                                              noise::random_double_noise(functions::random_double(0,15),0,1)), 5, 5);
    generateTest_Polygon("romboidRandomNoise5", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidRandomNoise5", romboid, romboid.getSeedPoints());
    romboid.printInFile("romboid.txt");
    romboid.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 10, 10);
    generateTest_Polygon("romboidRandom10", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidRandom10", romboid, romboid.getSeedPoints());
    romboid.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,15),0,1),
                                              noise::random_double_noise(functions::random_double(0,15),0,1)), 10, 10);
    generateTest_Polygon("romboidRandomNoise10", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidRandomNoise10", romboid, romboid.getSeedPoints());
    romboid.printInFile("romboid.txt");
    romboid.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    quarter_circle.printInFile("quarter_circle.txt");
    generateTest_Polygon("quarter_circleRandom5", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleRandom5", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,15),0,1),
                                                     noise::random_double_noise(functions::random_double(0,15),0,1)), 5, 5);
    generateTest_Polygon("quarter_circleRandomNoise5", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleRandomNoise5", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("quarter_circleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,15),0,1),
                                                     noise::random_double_noise(functions::random_double(0,15),0,1)), 10, 10);
    generateTest_Polygon("quarter_circleRandomNoise10", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleRandomNoise10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 5, 5);
    generateTest_Polygon("unicornNotSoRandom5", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornNotSoRandom5", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constantAlternating(),0,2),
                                              noise::random_double_noise(functions::constant(),0,2)), 5, 5);
    generateTest_Polygon("unicornNotSoRandomNoise5", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornNotSoRandomNoise5", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest_Polygon("unicornRandom10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.printInFile("unicorn.txt");
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::random_double(0,15),0,2),
                                              noise::random_double_noise(functions::random_double(0,20),0,2)), 5, 5);
    generateTest_Polygon("unicornRandomNoise10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornRandomNoise10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    /*-----------------------------------------------Uniform generation-------------------------------------------------*/
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("squareUniform10", square, square.getSeedPoints());
    generateTest_Triangle("squareUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constant(),0,1),
                                             noise::random_double_noise(functions::constant(),0,1)), 10, 10);
    generateTest_Polygon("squareUniformNoise10", square, square.getSeedPoints());
    generateTest_Triangle("squareUniformNoise10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("romboidUniform10", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidUniform10", romboid, romboid.getSeedPoints());
    romboid.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constant(),0,1),
                                              noise::random_double_noise(functions::constant(),0,1)), 10, 10);
    generateTest_Polygon("romboidUniformNoise10", romboid, romboid.getSeedPoints());
    generateTest_Triangle("romboidUniformNoise10", romboid, romboid.getSeedPoints());
    romboid.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("quarter_circleUniform10", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleUniform10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constant(),0,1),
                                                     noise::random_double_noise(functions::constant(),0,1)), 10, 10);
    generateTest_Polygon("quarter_circleUniformNoise10", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleUniformNoise10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();


    unicorn.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("unicornUniform10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornUniform10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(noise::random_double_noise(functions::constant(),0,1),
                                              noise::random_double_noise(functions::constant(),0,1)), 10, 10);
    generateTest_Polygon("unicornUniformNoise10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornUniformNoise10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    /*---------------------------------------Generation with holes------------------------------------*/
    Hole circular = CircularHole(Point(5,5), 2);
    square.addHole(circular);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest_Polygon("squareHoleCenterRandom5", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleCenterRandom5", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("squareHoleCenterRandom10", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleCenterRandom10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("squareHoleCenterUniform10", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleCenterUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();
    square.printInFile("SquareHole.txt");

    square = Region(square_points);

    circular = CircularHole(Point(5,10), 2);
    square.addHole(circular);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest_Polygon("squareHoleBorderRandom5", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleBorderRandom5", square, square.getSeedPoints());
    square.printInFile("squareHoleBorder");
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("squareHoleBorderRandom10", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleBorderRandom10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("squareHoleBorderUniform10", square, square.getSeedPoints());
    generateTest_Triangle("squareHoleBorderUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    Hole circular1 = CircularHole(Point(10,5), 2);
    Hole circular2 = CircularHole(Point(5,0), 2);
    Hole circular3 = CircularHole(Point(0,5), 2);
    square.addHole(circular1);
    square.addHole(circular2);
    square.addHole(circular3);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("squareSwissCheeseRandom10", square, square.getSeedPoints());
    generateTest_Triangle("squareSwissCheeseRandom10", square, square.getSeedPoints());
    square.printInFile("squareSwissCheese");
    square.cleanSeedPoints();
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("squareSwissCheeseUniform10", square, square.getSeedPoints());
    generateTest_Triangle("squareSwissCheeseUniform10", square, square.getSeedPoints());

    square.cleanSeedPoints();

    circular = CircularHole(Point(10,0), 4);
    quarter_circle.addHole(circular);
    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest_Polygon("quarter_circleHoleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    generateTest_Triangle("quarter_circleHoleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    Hole circle = CircularHole(Point(8,8), 2);
    unicorn.addHole(circle);
    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest_Polygon("unicornHoleInsideRandom10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornHoleInsideRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.printInFile("unicornHoleInside");
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("unicornHoleInsideUniform10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornHoleInsideUniform10", unicorn, unicorn.getSeedPoints());

    unicorn.cleanInternalHoles();
    circle = CircularHole(Point(5,5), 2);
    unicorn.addHole(circle);
    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest_Polygon("unicornHoleBorderRandom10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornHoleBorderRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.printInFile("unicornHoleBorder");
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest_Polygon("unicornHoleBorderUniform10", unicorn, unicorn.getSeedPoints());
    generateTest_Triangle("unicornHoleBorderUniform10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

}