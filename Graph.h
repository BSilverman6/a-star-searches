#ifndef GRAPH_H__
#define GRAPH_H__

#include "Edge.h"
#include "Node.h"
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>



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
  vector<Edge*> getEdges();
  void addNode(Node* n); //keep
  void addEdge(Edge* e); //keep
  void removeNode(Node* n); //keep
  void removeEdge(Edge* e); //keep
  set<Edge*> getAdjacentEdges(Node* n);

  void setUpMap(int dimension);
  queue <Node*> getShortestPath(Node* start, Node* end);


  
private:
  vector<vector<Node*>> nodes_map;
  vector<Edge*> edges;
  // The next two vectors may be used in your search algorithms.
  //vector<Edge*> search_edges;
  //vector<Node*> search_nodes;
};

#endif // GRAPH_H__