#ifndef NODE_H__
#define NODE_H__

#include <iostream>
#include <memory>

using namespace std;

//Terrain Types
#define FIELD 0
#define BRAMBLE 1
#define WALL 2

//A* Search Status (sets)
#define FAR 20
#define FRONTIER 21
#define EXPLORED 22



class Node {
private:
  int terrain_type;  // Feild, Water, etc.
  int x_co;
  int y_co;

  //Data for the Algorithm!
  int time_to_goal; //hueristic function - Time to Goal + Terrain Bunch Mod(?)
  int time_from_origin; //sum of all travel_times, includes cost to get to this one
  int search_stat;
  Node* last_visited;

public:
  Node(int x, int y, int tt);
  ~Node();
  int getTerrainType();
  int getXCo();
  int getYCo();

  void setTerrainType(int tt);
  void clearSearchStatus();

};

#endif
