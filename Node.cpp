#include "Node.h"

Node::Node(int x, int y, int tt) {
  terrain_type = tt;
  x_co = x;
  y_co = y;

  time_to_goal = -1;
  time_from_origin = -1;
  last_visited = nullptr;
  search_stat = FAR;
}

Node::~Node() {
}

int Node::getTerrainType() {
  return terrain_type;
}

int Node::getXCo(){
  return x_co;
}

int Node::getYCo(){
  return y_co;
}

void Node::setTerrainType(int tt){
  terrain_type = tt;
}

void Node::clearSearchStatus(){
  time_to_goal = -1;
  time_from_origin = -1;
  last_visited = nullptr;
  search_stat=FAR;
}

