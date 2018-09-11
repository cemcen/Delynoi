#include "delynoi/voronoi/DelaunayToVoronoi.h"

DelaunayToVoronoi::DelaunayToVoronoi(DelaunayInfo& del) {
    std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();
    SegmentMap* voronoiEdges = new SegmentMap;
    PointMap* pointMap = new PointMap;
    UniqueList<Polygon> voronoiCells;

    //std::cout << "Numero de puntos reales: " << del.realPoints.size() << std::endl;
    for(int i=0;i<del.realPoints.size(); i++) {
        std::vector<IndexSegment> thisEdges;

        int index = del.realPoints[i];
        UniqueList<int> cellPoints;
        Point regionCenter = del.meshPoints[index];
        EdgeData init_edge = del.edges[del.points[index].edge];

        int t1 = init_edge.t1;
        int t2 = init_edge.t2;

        int index1 = getCircumcenter(del, t1,del.points[index].edge);
        int index2 = getCircumcenter(del, t2,del.points[index].edge);

        if(index1!=index2){
            IndexSegment e (index2,index1);
            thisEdges.push_back(e);

            cellPoints.push_back(index2);
        }

        cellPoints.push_back(index1);
        EdgeData edge = del.edges[del.triangles[t1].nextEdge(index, init_edge, del.edgeMap)];

        int k = 0;
        while(!(edge==init_edge)){
            t2 = t1;
            t1 = edge.t1!=t2? edge.t1 : edge.t2;

            int currentEdge = del.edgeMap[Key(edge.p1, edge.p2)];

            index1 = getCircumcenter(del,t1,currentEdge);
            index2 = getCircumcenter(del,t2,currentEdge);

            if(index1!=index2){
                IndexSegment e (index2, index1);
                thisEdges.push_back(e);

                cellPoints.push_back(index2);
            }

            cellPoints.push_back(index1);
            k++;

            if(t1!=-1){
                edge = del.edges[del.triangles[t1].nextEdge(index, edge, del.edgeMap)];
            }else{
                //std::cout << "Iteraciones: " << k << std::endl;
                break;
            }
        }

        if(edge.t2==-1){
            int firstPoint = cellPoints[0];
            int lastPoint = cellPoints[cellPoints.size()-1];

            if(geometry_functions::collinear(del.circumcenters[firstPoint],regionCenter,del.circumcenters[lastPoint])){
                IndexSegment e (lastPoint, firstPoint);
                thisEdges.push_back(e);
            } else{
                regionCenter.setBoundary();
                int regionIndex = del.circumcenters.push_back(regionCenter);
                cellPoints.push_back(regionIndex);

                IndexSegment e1(lastPoint, regionIndex);
                IndexSegment e2(regionIndex, firstPoint);

                thisEdges.push_back(e1);
                thisEdges.push_back(e2);
            }
        }

        std::vector<Point>& pointList = del.circumcenters.getList();
        std::vector<int>& cellPointsList = cellPoints.getList();

        //Check if it is necessary to use a unique list for the polygons
        Polygon p = Polygon(cellPointsList, pointList);
        p.fixCCW(pointList);

        int cellIndex = voronoiCells.push_back(p);

        // Do this while you iterate
        for (int j = 0; j < thisEdges.size(); ++j) {
            voronoiEdges->insert(thisEdges[j], cellIndex);
        }

        for (int k = 0; k < cellPoints.size(); ++k) {
            pointMap->insert(del.circumcenters[cellPoints[k]], cellIndex);
        }
    }

    std::vector<Point> points = del.circumcenters.getList();
    std::vector<Polygon> cells = voronoiCells.getList();
    std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( time2 - time1 ).count();

    std::cout <<  " Tiempo: " << duration << std::endl;


    this->mesh = Mesh<Polygon>(points, cells, voronoiEdges, pointMap);
}


int DelaunayToVoronoi::getCircumcenter(DelaunayInfo& del, int triangle, int edge) {
    if(triangle!=-1){
        return del.triangles[triangle].getCircumcenterIndex();
    }else{
        Point middlePoint = IndexSegment(del.edges[edge].p1, del.edges[edge].p2).middlePoint(del.meshPoints);
        middlePoint.setBoundary();

        int circumcenterIndex = del.circumcenters.push_back(middlePoint);

        return circumcenterIndex;
    }
}

Mesh<Polygon>& DelaunayToVoronoi::getMesh() {
    return this->mesh;
}
