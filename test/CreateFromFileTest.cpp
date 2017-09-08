#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/Mesh.h>

int main(){
    Mesh<Polygon> mesh;
    mesh.createFromFile("ExampleMesh.txt");
}