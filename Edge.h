#ifndef EDGE_H__
#define EDGE_H__

#include "Node.h"
#include <memory>
#include <cmath>

using namespace std;

//Types of Edges
#define FIELD_FIELD 10
#define BRAMBLE_BRAMBLE 11
#define FIELD_BRAMBLE 12
#define CORNER_LEN 1.41

class Edge {
private:
  Node* a;  // a node
  Node* b;  // b node
  int path_type; //Type of Edge 
  float time_mod; // 1 (easy) or 1.5 (bridge) or 2 (difficult)
  float length; // 1 or 1.41 
  int travel_time; //len*time_mod

public:
  Edge(Node* n1, Node* n2);
  ~Edge();
  Node* getStart();
  Node* getEnd();

  void setPathInfo ();
  float getTravelTime();

};
#endif // EDGE
