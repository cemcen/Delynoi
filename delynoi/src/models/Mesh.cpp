#include <delynoi/models/Mesh.h>
#include <utilities/utilities.h>


Mesh::Mesh() {}

Mesh::Mesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
}

Mesh::Mesh(const Mesh &m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
}


void Mesh::createFromFile(std::string fileName) {
    std::string completeName = utilities::getPath() + fileName;
    std::ifstream infile(completeName);

    createFromStream(infile);

    infile.close();
}

void Mesh::createFromStream(std::ifstream &infile) {
    std::string line;
    std::getline(infile, line);
    int numberMeshPoints = std::atoi(line.c_str());
    for (int i = 0; i < numberMeshPoints; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::split(line, ' ');

        Point newPoint(std::atof(splittedLine[0].c_str()), std::atof(splittedLine[1].c_str()));
        this->points.push_back(newPoint);
    }

    std::getline(infile, line);
    int numberMeshPolygons = std::atoi(line.c_str());

    for (int i = 0; i < numberMeshPolygons; ++i) {
        std::getline(infile, line);
        std::vector<std::string> splittedLine = utilities::split(line, ' ');

        std::vector<int> polygonPoints;
        for (int j = 1; j < splittedLine.size(); ++j) {
            polygonPoints.push_back(std::atoi(splittedLine[j].c_str()) - 1);
        }

        Polygon newPolygon(polygonPoints, this->points.getList());
        this->polygons.push_back(newPolygon);
        std::vector<IndexSegment> segments;
        newPolygon.getSegments(segments);

        for (IndexSegment s: segments){
            this->edges.insert(s, i);
        }
    }
}

void Mesh::printInFile(std::string fileName) {
    std::string path = utilities::getPath();
    path +=  fileName;

    std::ofstream file;
    file.open(path, std::ios::out);
    file << std::fixed << std::setprecision(DelynoiConfig::instance()->getPrecision());

    printInStream(file);
    file.close();
}

std::vector<Polygon>& Mesh::getPolygons() {
    return this->polygons;
}

std::vector<Polygon> Mesh::getPolygons() const {
    return this->polygons;
}

Polygon& Mesh::getPolygon(int index) {
    return this->polygons[index];
}

void Mesh::printInStream(std::ofstream &file) {
    file << points.size() << std::endl;
    for(int i=0;i<points.size();i++){
        file << points[i].getString() << std::endl;
    }

    file << this->edges.size() << std::endl;
    for(auto e: this->edges.getMap()){
        IndexSegment edge = e.first;
        file << edge.getString() << std::endl;
    }

    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }
}

SegmentMap &Mesh::getSegments() {
    return this->edges;
}

SegmentMap Mesh::getSegments() const {
    return this->edges;
}

UniqueList <Point> &Mesh::getPoints() {
    return this->points;
}

UniqueList <Point> Mesh::getPoints() const {
    return this->points;
}

Point Mesh::getPoint(int i) {
    return this->points[i];
}

Neighbours Mesh::getNeighbours(IndexSegment s) {
    return this->edges.get(s);
}
