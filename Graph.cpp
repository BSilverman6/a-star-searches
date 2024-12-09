#include "Graph.h"

#include <iostream>
#include <sstream>
#include <queue>

using namespace std;


Graph::Graph() {
}

Graph::~Graph() {
}

vector<vector<Node*>> Graph::getNodes() {
  return nodes_map;
}

/*
 void Graph::addNode(Node* n) {
  nodes.push_back(n);
} 
 
void Graph::addEdge(Edge* e) {
  edges.push_back(e);
}

vector<Edge*> Graph::getEdges() {
  return edges;
}

 void Graph::removeNode(Node* n) {
  // From Graph HW Assignment
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(Edge* e) {
  // From Graph HW Assignment
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}


set<Edge*> Graph::getAdjacentEdges(Node* n) {
  //Modified from Graph HW Assignment
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == n || edge->getEnd() == n) {
      ret.insert(edge);
    }
  }
  return ret;
} */


void Graph::setUpMap(int dim){
  dimension = dim;
  //sets up all Nodes
  for (int i = 0; i< dimension; i++){
    vector<Node*> my_vec;
    for (int j = 0; j<dimension; j++){
      Node* node = new Node(j, i, FIELD);
      my_vec.push_back(node);
    }
    nodes_map.push_back(my_vec);
  }

  //For Testing Purposes
  nodes_map[2][2]->setTerrainType(WALL);
  set<Node*> my_set = getValidNeighbors(nodes_map[2][3]);
  cout<< "Check the Set!" << endl;
}

//This is IT! The Algorithm
//queue <Node*>  Graph::getShortestPath(Node* start, Node* end){
  //Make a PQueue
  //Make a Travel Time Float
  //Pop from the PQueue (Start)
  //Increase Travel Time

  //add Popped to Explored
  //get adjacent nodes to explored via edges
    //IF coming from blank
    //assign each node times to goal, origin, and last visited
    //IF coming from OPTION
    //compare the value and delete/re-insert into pque if smaller
    //IF EXPLORED
    //do nothing.
//}

//This is where I switch from "Computer Array Axes" to 
//standard math array axes
//nodes_map[row (y)][column (x)]
set <Node*> Graph::getValidNeighbors (Node* my_node){
  set <Node*> ret;
  int x = my_node->getXCo();
  int y = my_node->getYCo();

  //8 possible neighbors
  //t-top, b-bottom, l-left, r-right
  bool tl = true;
  bool t = true;
  bool tr = true;
  bool r = true;
  bool br = true;
  bool b = true;
  bool bl = true;
  bool l = true;

  if (x == 0 || nodes_map[y][x-1]->getTerrainType() == WALL){
    tl = false; l = false; bl = false;
  }
  if (y == 0|| nodes_map[y-1][x]->getTerrainType() == WALL){
    bl = false; b = false; br = false;
  }
  if (x == dimension-1|| nodes_map[y][x+1]->getTerrainType() == WALL){
    br = false; r = false; tr = false;
  }
  if (y == dimension-1|| nodes_map[y+1][x]->getTerrainType() == WALL){
    tr = false; t = false; tl = false;
  }

  if (t){ret.insert(nodes_map[y+1][x]);}
  if (r){ret.insert(nodes_map[y][x+1]);}
  if (b){ret.insert(nodes_map[y-1][x]);}
  if (l){ret.insert(nodes_map[y][x-1]);}

  if (tl && nodes_map[y+1][x-1]->getTerrainType() != WALL){ret.insert(nodes_map[y+1][x-1]);}
  if (tr && nodes_map[y+1][x+1]->getTerrainType() != WALL){ret.insert(nodes_map[y+1][x+1]);}
  if (br && nodes_map[y-1][x+1]->getTerrainType() != WALL){ret.insert(nodes_map[y-1][x+1]);}
  if (bl && nodes_map[y-1][x-1]->getTerrainType() != WALL){ret.insert(nodes_map[y-1][x-1]);}

  return ret;


}
