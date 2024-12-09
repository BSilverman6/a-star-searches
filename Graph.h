#ifndef GRAPH_H__
#define GRAPH_H__

#include "Edge.h"
#include "Node.h"
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define FIELD_FIELD 10
#define BRAMBLE_BRAMBLE 11
#define FIELD_BRAMBLE 12
#define CORNER_LEN 1.41

using namespace std;

/* struct Coord{
  int x;
  int y;
}; */

class Graph {
public:
  // The first block of public members are implemented for you.
  Graph();
  ~Graph();
  vector<vector<Node*>> getNodes();
  void addNode(Node* n); //keep
  void removeNode(Node* n); //keep

  void setUpMap(int dimension);
  queue <Node*> getShortestPath(Node* start, Node* end);


  
private:
  set <Node*> getValidNeighbors (Node* my_node);
  vector<vector<Node*>> nodes_map;
  int dimension;
  
  // The next two vectors may be used in your search algorithms.
  //vector<Node*> search_nodes;

  //taken fron old Edge Class.
  int path_type; //Type of Edge 
  float time_mod; // 1 (easy) or 1.5 (bridge) or 2 (difficult)
  float length; // 1 or 1.41 
  int travel_time; //len*time_mod
};

#endif // GRAPH_H__