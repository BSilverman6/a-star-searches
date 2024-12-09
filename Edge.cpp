#include "Edge.h"

Edge::Edge(Node* n1, Node* n2) {
  a = n1;
  b = n2;

  setPathInfo();
  //set type
    //set time mod
  //set length

  //set travel time
}

Edge::~Edge() {
}


Node* Edge::getStart(){
  return a;
}

Node* Edge::getEnd(){
  return b;
}

void Edge::setPathInfo (){
  int a_terr = a->getTerrainType();
  int b_terr = b->getTerrainType();
  
  //Sets the Type of Edge and Time Modifier.
  if (a_terr == FIELD && b_terr == FIELD){
    path_type = FIELD_FIELD;
    time_mod = 1;
  }
  else if (a_terr == BRAMBLE && b_terr == BRAMBLE){
    path_type = BRAMBLE_BRAMBLE;
    time_mod = 2;
  }
  else{
    path_type = FIELD_BRAMBLE;
    time_mod = 1.5;
  }

 int a_x_co = a->getXCo();
 int a_y_co = a->getYCo();
 int b_x_co = b->getXCo();
 int b_y_co = b->getYCo();

  if (a_x_co == b_x_co || a_y_co == b_y_co){
    length = 1;
  }
  else{
    length = CORNER_LEN; //1.41
  }

  travel_time = length*time_mod;
}





float Edge::getTravelTime() {
  return travel_time;
}

