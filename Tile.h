#ifndef TILE_H__
#define TILE_H__

#include <iostream>


using namespace std;

//Terrain Types
#define FIELD 0
#define BRAMBLE 1
#define WALL 2

//A* Search Status (sets)
#define FAR 20
#define FRONTIER 21
#define EXPLORED 22
#define PATH 23



class Tile {

public:

  //default constructor
  //unused because the Grid System with a matching x/y
  //makes lookup WAY faster
  Tile();

  //the constructor that I used
  Tile(int x, int y);

  ~Tile();

  //getters, self explanitory

  int getTerrainType();
  int getXCoord();
  int getYCoord();
  double getFCost();
  double getGCost(); //based on optimal Tile* Last Visited

//For Creativity in Debugging.
//I need Walls and Brambles to Test the algorithm
  void setTerrainType(int tt);

//Resets the variables used in the Search
  void clearSearchStatus();

  //set's the costs used in A* Search
  //Only get's called if this specific tile is
  //either FAR or a more efficient path to it is found
  void setCosts(double h, double g, Tile* curr);
  
  //Only used to set the g_cost of the starting
  //Tile to 0.
  void setGCost(double g);

  //Other Getters and Setters
  void setSearchStat(int ss);
  int getSearchStat();
  Tile* getLastVisited();

  

  bool operator()(Tile* a, Tile* b){
  if (a->f_cost > b->f_cost){
    return true;
  }
  else if (a->f_cost==b->f_cost && a->h_cost>b->h_cost){
    return true;
  }
  else return false;
  };

private:
  int terrain_type;  // Feild, Water, etc.
  int x_co;
  int y_co;

  //Data for the Algorithm!
  //Used in Search Status 
  double h_cost; //h-cost, hueristic function - Time to Goal + Terrain Bunch Mod(?)
  double g_cost; //g-cost, sum of all travel_times, includes cost to get to this one
  double f_cost; //f-cost, sum of g+h costs.
  int search_stat;
  Tile* last_visited;

  


};

#endif
