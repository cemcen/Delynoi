#include <delynoi/models/basic/Point.h>
#include <utilities/UniqueList.h>
#include <fstream>
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/structures/PointData.h>
#include <delynoi/models/neighbourhood/EdgeData.h>
#include <delynoi/models/polygon/Triangle.h>
#include <delynoi/models/neighbourhood/PointMap.h>
#include <chrono>

extern "C"{
#include <delynoi/voronoi/lib/triangle.h>
};

int main(){
    std::vector<int> numberOfPoints = {2,3,5,6,10,12,15,20,25,30,35,40,45,50,55};
    //std::vector<int> numberOfPoints = {2,3,5};

    std::string path = utilities::getPath();
    path += "time_results.txt";

    std::ofstream file;
    file.open(path, std::ios::out);

    for (int i = 0; i < numberOfPoints.size(); ++i) {
        std::vector<Point> square_points = {Point(0, 0), Point(10, 0), Point(10, 10), Point(0, 10)};
        Region square(square_points);

        square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), numberOfPoints[i],
                                  numberOfPoints[i]);
        std::vector<Point> seeds = square.getSeedPoints();

        std::vector<Triangle> triangles;
        std::vector<PointData> pointData;
        std::vector<int> realPoints;
        std::vector<EdgeData> edges;
        std::vector<Point> circumcenters;
        std::unordered_map<Key, int, KeyHasher> edgeMap;
        SegmentMap* delaunayEdges = new SegmentMap;
        std::vector<Point> meshPoints;

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Numero de puntos: " << numberOfPoints[i]*numberOfPoints[i];

        struct triangulateio in, out;

        std::vector<Point> regionPoints = square.getRegionPoints();
        UniqueList<Point> pointList;
        pointList.push_list(seeds);
        std::vector<int> regionIndex = pointList.push_list(regionPoints);

        in.numberofpoints = pointList.size();
        in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
        in.numberofpointattributes = 1;
        in.pointattributelist = (REAL *) malloc(in.numberofpoints * in.numberofpointattributes * sizeof(REAL));
        int points = 0;

        for (int i = 0; i < pointList.size(); i++) {
            in.pointlist[points] = pointList[i].getX();
            in.pointlist[points + 1] = pointList[i].getY();
            in.pointattributelist[i] = 0.0;
            points += 2;
        }

        in.pointmarkerlist = (int *) NULL;

        std::vector<IndexSegment> segments;
        square.getSegments(segments);

        in.numberofsegments = (int) (segments.size());
        in.segmentlist = (int *) malloc(in.numberofsegments * 2 * sizeof(int));
        in.segmentmarkerlist = (int *) NULL;
        int k;
        for (k = 0; k < segments.size(); k++) {
            in.segmentlist[2 * k] = regionIndex[segments[k].getFirst()];
            in.segmentlist[2 * k + 1] = regionIndex[segments[k].getSecond()];
        }

        std::vector<Hole> &holes = square.getHoles();
        in.numberofholes = (int) holes.size();
        in.holelist = (REAL *) malloc(in.numberofholes * 2 * sizeof(REAL));
        for (int i = 0; i < holes.size(); i++) {
            in.holelist[2 * i] = holes[i].getCenter().getX();
            in.holelist[2 * i + 1] = holes[i].getCenter().getY();
        }

        in.numberofregions = 0;

        out.pointlist = (REAL *) NULL;
        out.pointattributelist = (REAL *) NULL;
        out.pointmarkerlist = (int *) NULL;
        out.trianglelist = (int *) NULL;
        out.triangleattributelist = (REAL *) NULL;
        out.segmentmarkerlist = (int *) NULL;
        out.segmentlist = (int *) NULL;
        out.edgelist = (int *) NULL;
        out.edgemarkerlist = (int *) NULL;

        char switches[] = "pzejDQ";
        triangulate(switches, &in, &out, (struct triangulateio *) NULL);

        for (int i = 0; i < out.numberofpoints; i++) {
            PointData data(i);
            pointData.push_back(data);
            meshPoints.push_back(Point(out.pointlist[i * 2], out.pointlist[i * 2 + 1]));
            if (out.pointmarkerlist[i] == 1) {
                meshPoints.back().setBoundary();
            }
        }

        for (int i = 0; i < out.numberofedges; i++) {
            EdgeData data(out.edgelist[2 * i], out.edgelist[2 * i + 1]);
            edges.push_back(data);
            edgeMap.insert(std::make_pair(Key(out.edgelist[2 * i], out.edgelist[2 * i + 1]), i));
            pointData[out.edgelist[2 * i]].setEdge(i, out.edgemarkerlist[i]);
            pointData[out.edgelist[2 * i + 1]].setEdge(i, out.edgemarkerlist[i]);
        }

        for (int i = 0; i < out.numberoftriangles; i++) {
            std::vector<int> triangle_points = {out.trianglelist[3 * i], out.trianglelist[3 * i + 1],
                                                out.trianglelist[3 * i + 2]};
            realPoints.push_back(out.trianglelist[3 * i]);
            realPoints.push_back(out.trianglelist[3 * i + 1]);
            realPoints.push_back(out.trianglelist[3 * i + 2]);

            Triangle triangle(triangle_points, meshPoints, circumcenters);
            int i1 = edgeMap[Key(out.trianglelist[3 * i], out.trianglelist[3 * i + 1])];
            int i2 = edgeMap[Key(out.trianglelist[3 * i + 1], out.trianglelist[3 * i + 2])];
            int i3 = edgeMap[Key(out.trianglelist[3 * i + 2], out.trianglelist[3 * i])];

            edges[i1].setTriangle(i);
            edges[i2].setTriangle(i);
            edges[i3].setTriangle(i);

            triangles.push_back(triangle);
        }

        for (int i = 0; i < edges.size(); ++i) {
            EdgeData data = edges[i];
            IndexSegment segment(data.p1, data.p2);
            NeighboursBySegment neighbours(data.t1, data.t2);

            delaunayEdges->insert(segment, neighbours);
        }

        free(in.pointlist);
        free(in.pointattributelist);
        free(in.pointmarkerlist);
        free(in.segmentlist);
        free(in.segmentmarkerlist);
        free(in.holelist);

        free(out.pointlist);
        free(out.pointattributelist);
        free(out.pointmarkerlist);
        free(out.trianglelist);
        free(out.triangleattributelist);
        free(out.segmentmarkerlist);
        free(out.segmentlist);
        free(out.edgelist);
        free(out.edgemarkerlist);

        SegmentMap* voronoiEdges = new SegmentMap;
        PointMap* pointMap = new PointMap;
        std::vector<Polygon> voronoiCells;

        //std::cout << "Numero de puntos reales: " << del.realPoints.size() << std::endl;
        for(int i=0;i<realPoints.size(); i++) {
            int cellIndex = voronoiCells.size();
            std::vector<IndexSegment> thisEdges;

            int index = realPoints[i];
            UniqueList<int> cellPoints;
            Point regionCenter = meshPoints[index];
            EdgeData init_edge = edges[pointData[index].edge];

            int t1 = init_edge.t1;
            int t2 = init_edge.t2;

            int index1, index2;

            if(t1!=-1){
                index1 = triangles[t1].getCircumcenterIndex();
            }else{
                int edge = pointData[index].edge;

                Point middlePoint = IndexSegment(edges[edge].p1, edges[edge].p2).middlePoint(meshPoints);
                middlePoint.setBoundary();

                int circumcenterIndex = circumcenters.size();
                circumcenters.push_back(middlePoint);

                index1 = circumcenterIndex;
            }

            if(t2!=-1){
                index2 = triangles[t2].getCircumcenterIndex();
            }else{
                int edge = pointData[index].edge;

                Point middlePoint = IndexSegment(edges[edge].p1, edges[edge].p2).middlePoint(meshPoints);
                middlePoint.setBoundary();

                int circumcenterIndex = circumcenters.size();
                circumcenters.push_back(middlePoint);

                index2 = circumcenterIndex;
            }

            if(index1!=index2){
                IndexSegment e (index2,index1);
                thisEdges.push_back(e);
                voronoiEdges->insert(e, cellIndex);

                cellPoints.push_back(index2);
                //      pointMap->insert(del.circumcenters[index2], cellIndex);
            }

            cellPoints.push_back(index1);
            //pointMap->insert(del.circumcenters[index1], cellIndex);

            EdgeData edge = edges[triangles[t1].nextEdge(index, init_edge, edgeMap)];

            while(!(edge==init_edge)){
                t2 = t1;
                t1 = edge.t1!=t2? edge.t1 : edge.t2;

                int currentEdge = edgeMap[Key(edge.p1, edge.p2)];

                if(t1!=-1){
                    index1 = triangles[t1].getCircumcenterIndex();
                }else{
                    Point middlePoint = IndexSegment(edges[currentEdge].p1, edges[currentEdge].p2).middlePoint(meshPoints);
                    middlePoint.setBoundary();

                    int circumcenterIndex = circumcenters.size();
                    circumcenters.push_back(middlePoint);

                    index1 = circumcenterIndex;
                }

                if(t2!=-1){
                    index2 = triangles[t2].getCircumcenterIndex();
                }else{
                    Point middlePoint = IndexSegment(edges[currentEdge].p1, edges[currentEdge].p2).middlePoint(meshPoints);
                    middlePoint.setBoundary();

                    int circumcenterIndex = circumcenters.size();
                    circumcenters.push_back(middlePoint);

                    index2 = circumcenterIndex;
                }

                if(index1!=index2){
                    IndexSegment e (index2, index1);

                    thisEdges.push_back(e);
                    voronoiEdges->insert(e, cellIndex);

                    cellPoints.push_back(index2);
                    //pointMap->insert(del.circumcenters[index2], cellIndex);
                }

                cellPoints.push_back(index1);
                //pointMap->insert(del.circumcenters[index1], cellIndex);


                if(t1!=-1){
                    edge = edges[triangles[t1].nextEdge(index, edge, edgeMap)];
                }else{
                    //std::cout << "Iteraciones: " << k << std::endl;
                    break;
                }
            }

            if(edge.t2==-1){
                int firstPoint = cellPoints[0];
                int lastPoint = cellPoints[cellPoints.size()-1];

                if(geometry_functions::collinear(circumcenters[firstPoint],regionCenter,circumcenters[lastPoint])){
                    IndexSegment e (lastPoint, firstPoint);
                    thisEdges.push_back(e);

                    voronoiEdges->insert(e, cellIndex);
                } else{
                    regionCenter.setBoundary();
                    int regionIndex = circumcenters.size();
                    circumcenters.push_back(regionCenter);

                    cellPoints.push_back(regionIndex);
                    //  pointMap->insert(del.circumcenters[regionIndex], cellIndex);

                    IndexSegment e1(lastPoint, regionIndex);
                    IndexSegment e2(regionIndex, firstPoint);

                    thisEdges.push_back(e1);
                    voronoiEdges->insert(e1, cellIndex);

                    thisEdges.push_back(e2);
                    voronoiEdges->insert(e2, cellIndex);
                }
            }

            std::vector<int>& cellPointsList = cellPoints.getList();

            //Check if it is necessary to use a unique list for the polygons
            // You do not need a pointmap per se, check what happens if not filled.

            Polygon p = Polygon(cellPointsList, circumcenters);
            p.fixCCW(circumcenters);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        file << "Numero de puntos: " << numberOfPoints[i]*numberOfPoints[i] << " Tiempo: " << duration << std::endl;
    }

    return 0;
}