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


void Graph::setUpMap(int dimension){
  
  //sets up all Nodes
  for (int i = 0; i< dimension; i++){
    vector<Node*> row_vec;
    for (int j = 0; j<dimension; j++){
      Node* node = new Node(i, j, FIELD);
      row_vec.push_back(node);
    }
    nodes_map.push_back(row_vec);
  }
/* 
  //Add and Classifly Edges
  for (int i = 0; i < dimension-1; i++){
    for (int j = 0; j < dimension-1; j++){
      //sets up horizontal Edges
      Edge* horiz_edge = new Edge(nodes_map[i][j],nodes_map[i][j+1]);
      edges.push_back(horiz_edge);
      //sets up Vertical Edges
      Edge* vert_edge = new Edge(nodes_map[i][j],nodes_map[i+1][j]);
      edges.push_back(vert_edge);
      
      //No Diagonal Edges if any one of the four is a WALL
      //sets up Diagonal Edge
      Edge* diag_edge = new Edge(nodes_map[i][j],nodes_map[i+1][j+1]);
      edges.push_back(diag_edge);
      //sets Up Other Diagonal Edge
      Edge* diag_edge2 = new Edge(nodes_map[i+1][j],nodes_map[i][j+1]);
      edges.push_back(diag_edge2);

    }
  }
  //sets up the last of the edges
  for (int k = 0; k<dimension-1; k++){
    Edge* horiz_edge = new Edge(nodes_map[dimension-1][k],nodes_map[dimension-1][k+1]);
    edges.push_back(horiz_edge);
    Edge* vert_edge = new Edge(nodes_map[k][dimension-1],nodes_map[k+1][dimension-1]);
    edges.push_back(vert_edge);
  } */
}

//This is IT! The Algorithm
queue <Node*>  Graph::getShortestPath(Node* start, Node* end){
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
}