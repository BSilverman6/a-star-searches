#include "Tile.h"
#include <cmath>

Tile::Tile() {
}

Tile::Tile(int x, int y) {
  x_co = x;
  y_co = y;

  terrain_type = FIELD;
  h_cost = -1;
  g_cost = -1;
  f_cost = -1;
  last_visited = nullptr;
  search_stat = FAR;
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

double Tile::getFCost(){
  return f_cost;
}

double Tile::getGCost(){
  return g_cost;
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


void Tile::setCosts(double h, double g, Tile* curr){
  h_cost = h;
  g_cost = g;
  f_cost = h+g;
  search_stat = FRONTIER;
  last_visited = curr;
}

void Tile::setGCost(double g){
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



