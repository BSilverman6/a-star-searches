#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.cpp"
#include "Node.cpp"
#include "Edge.cpp"


#include <iostream>

using namespace std;

int main(){
    Graph* my_graph = new Graph();

    my_graph->setUpMap(4);

    cout << "Hello World" <<endl;
    return 0;
}