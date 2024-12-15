#include "Tile.h"
#include <cmath>

Tile::Tile() {
}

Tile::Tile(int x, int y) {
  x_co = x;
  y_co = y;

  terrain_type = FIELD;
  h_cost = -1; //HEURISTIC (estimated travel to end))
  g_cost = -1; //time to GET to this tile
  f_cost = -1; //time 
  last_visited = nullptr;
  search_stat = FAR;

  occupied_stat = EMPTY;
}

Tile::~Tile() {
}

int Tile::getTerrainType() {
  return terrain_type;
}

int Tile::getXCoord(){
  return x_co;
}

int Tile::getYCoord(){
  return y_co;
}

int Tile::getFCost(){
  return f_cost;
}

int Tile::getGCost(){
  return g_cost;
}

int Tile::getHCost(){
  return h_cost;
}

void Tile::setTerrainType(int tt){
  terrain_type = tt;
}

void Tile::clearSearchStatus(){
  h_cost = -1;
  g_cost = -1;
  f_cost = -1;
  last_visited = nullptr;
  search_stat=FAR;
}


void Tile::setCosts(int h, int g, Tile* curr){
  h_cost = h;
  g_cost = g;
  f_cost = h+g;
  search_stat = FRONTIER;
  last_visited = curr;
}

void Tile::setGCost(int g){
  g_cost = g;
}


void Tile::setSearchStat(int ss){
  search_stat = ss;
}

int Tile::getSearchStat(){
  return search_stat;
}

Tile* Tile::getLastVisited(){
  return last_visited;
}

void Tile::setOccupiedStat(int os){
  occupied_stat = os;
}

int Tile::getOccupiedStat(){
  return occupied_stat;
}


//Final Commit