#include <delynoi/models/PolygonalMesh.h>

PolygonalMesh::PolygonalMesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s) {
    this->points.push_list(p);
    this->polygons.assign(e.begin(), e.end());
    this->edges = s;
}

PolygonalMesh::PolygonalMesh() {}

void PolygonalMesh::createFromFile(std::string fileName) {
    std::string completeName = utilities::getPath() + fileName;
    std::ifstream infile(completeName);

    createFromStream(infile);

    infile.close();
}

void PolygonalMesh::createFromStream(std::ifstream &infile) {
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

PolygonalMesh::PolygonalMesh(const PolygonalMesh &m) {
    this->points = m.getPoints();
    this->polygons = m.getPolygons();
    this->edges = m.getSegments();
}

std::vector<Polygon>& PolygonalMesh::getPolygons() {
    return this->polygons;
}

std::vector<Polygon> PolygonalMesh::getPolygons() const {
    return this->polygons;
}

Polygon& PolygonalMesh::getPolygon(int index) {
    return this->polygons[index];
}

void PolygonalMesh::writeElements(std::ofstream &file) {
    file << this->polygons.size() << std::endl;
    for(int i=0;i<this->polygons.size();i++){
        file << this->polygons[i].getString() << std::endl;
    }
}



