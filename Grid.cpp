#include "Grid.h"
#include "Tile.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>
#include <vector>
#include <string>


using namespace std;


Grid::Grid() {
}

Grid::~Grid() {
}

vector<vector<Tile*>> Grid::getTiles() {
  return tiles_map;
}


void Grid::setUpMap(int dim){
  dimension = dim;
  //sets up all Tiles as FIELD Tiles
  for (int row = 0; row< dimension; row++){
    vector<Tile*> my_vec;
    for (int column = 0; column<dimension; column++){
      Tile* tile = new Tile(column, row);
      my_vec.push_back(tile);
    }
    tiles_map.push_back(my_vec);
  }

//Testing below here
  tiles_map[4][1]->setTerrainType(WALL);
  tiles_map[4][2]->setTerrainType(WALL);
  tiles_map[4][3]->setTerrainType(WALL);
  tiles_map[4][4]->setTerrainType(WALL);
  tiles_map[4][5]->setTerrainType(WALL);
  tiles_map[4][6]->setTerrainType(WALL);
  /* tiles_map[4][7]->setTerrainType(BRAMBLE);
  tiles_map[4][8]->setTerrainType(BRAMBLE);
  tiles_map[3][7]->setTerrainType(BRAMBLE);
  tiles_map[3][8]->setTerrainType(BRAMBLE);
  tiles_map[5][8]->setTerrainType(BRAMBLE);
  tiles_map[5][7]->setTerrainType(BRAMBLE); */



  //Testing purposes
}

double Grid::calc_h_cost(Tile* tile, Tile* end){
  int t_x = tile->getXCoord();
  int t_y = tile->getYCoord();
  int e_x = end->getXCoord();
  int e_y = end->getYCoord();
  int dx = abs(t_x - e_x);
  int dy = abs(t_y - e_y);
  double dist = (dx+dy)+(sqrt(2)-(2))*min(dx,dy);
  return dist;
}

//This is IT! The Algorithm
vector <Tile*>  Grid::getShortestPath(int sx, int sy, int ex, int ey){
  Tile* start = tiles_map[sy][sx];
  Tile* end = tiles_map[ey][ex];
  
  set <Tile*> active_tiles; //All tiles that I'm using are in here
  active_tiles.insert(start);
      print_grid();
  start->setSearchStat(EXPLORED);
  start->setGCost(0);
      print_grid();
  a_star_queue next_best_move;
  Tile* current_tile = start;

  do{
    set <Tile*> neighbors = getValidNeighbors(current_tile);
    for (auto n: neighbors){
      int n_search_stat = n->getSearchStat();
      if (n_search_stat != EXPLORED){
        
        //calc all the things
        double h_cost = calc_h_cost(n, end);
        double g_cost = current_tile->getGCost()+calc_travel_time(current_tile, n);

        if (n_search_stat == FAR||
            (n_search_stat == FRONTIER && n->getFCost()> h_cost+g_cost)){
          n->setCosts(h_cost,g_cost,current_tile);
          next_best_move.push(n);
        }
      }
    }

    //discards any previously explored tiles
    //that remain in the queue ()
    do{
      current_tile = next_best_move.top();
      next_best_move.pop();
    } while (current_tile->getSearchStat() == EXPLORED && !next_best_move.empty());

    print_grid();
    current_tile->setSearchStat(EXPLORED);

  }while (current_tile !=end && !next_best_move.empty());
  //Follows the Exit back to the Entrance
  vector <Tile*> ret;
  Tile* path_tile = current_tile;
  ret.push_back(path_tile);
  path_tile->setSearchStat(PATH);
  do{
    path_tile = path_tile->getLastVisited();
    ret.push_back(path_tile);
    path_tile->setSearchStat(PATH);

  } while(path_tile != start);

      print_grid();

  for(auto v: tiles_map){
    for (auto t: v){
      t->clearSearchStatus();
    }
  }

    print_grid();
  return ret;
}

//Confusing Note - Here I visualize x and y in
//a positive cartesian coordinate system
//although rows/columns in a 2d Vector are flipped
//x/y where top left is 0,0 getting higher moving
//bottom right.
//
//tiles_map[row (y)][column (x)]
set <Tile*> Grid::getValidNeighbors (Tile* my_tile){
  set <Tile*> ret;
  int x = my_tile->getXCoord();
  int y = my_tile->getYCoord();

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

//If one of the vert/horiz sides is a WALL or Map Edge,
//that and the two adjacent tiles are not navigable from here
  if (x == 0 || tiles_map[y][x-1]->getTerrainType() == WALL){
    tl = false; l = false; bl = false;
  }
  if (y == 0|| tiles_map[y-1][x]->getTerrainType() == WALL){
    bl = false; b = false; br = false;
  }
  if (x == dimension-1|| tiles_map[y][x+1]->getTerrainType() == WALL){
    br = false; r = false; tr = false;
  }
  if (y == dimension-1|| tiles_map[y+1][x]->getTerrainType() == WALL){
    tr = false; t = false; tl = false;
  }

  //Inserts possible vert/horiz neighbors for return
  if (t){ret.insert(tiles_map[y+1][x]);}
  if (r){ret.insert(tiles_map[y][x+1]);}
  if (b){ret.insert(tiles_map[y-1][x]);}
  if (l){ret.insert(tiles_map[y][x-1]);}

  //inserts possible diagonal neighbors for return (no insert if it is a wall)
  if (tl && tiles_map[y+1][x-1]->getTerrainType() != WALL){ret.insert(tiles_map[y+1][x-1]);}
  if (tr && tiles_map[y+1][x+1]->getTerrainType() != WALL){ret.insert(tiles_map[y+1][x+1]);}
  if (br && tiles_map[y-1][x+1]->getTerrainType() != WALL){ret.insert(tiles_map[y-1][x+1]);}
  if (bl && tiles_map[y-1][x-1]->getTerrainType() != WALL){ret.insert(tiles_map[y-1][x-1]);}

  return ret;
}

//untested
//works based on printed numbers in printed Visual!
double Grid::calc_travel_time (Tile* current, Tile* neighbor){
  //2 fields
  double modifier = 1.0;
  double distance = 1.0;

  if ((current->getTerrainType() == BRAMBLE && neighbor->getTerrainType() == FIELD)
      || (current->getTerrainType() == FIELD && neighbor->getTerrainType() == BRAMBLE)){
      modifier = 1.5;
  }
  if (current->getTerrainType() == BRAMBLE && neighbor->getTerrainType() == BRAMBLE){
      modifier = 2.0;
  }

  if (current->getXCoord() != neighbor->getXCoord() && current->getYCoord() != neighbor->getYCoord()){
    distance = 1.41;
  }

  double ret = modifier*distance;
  ret = round(ret*100)/100;
  return ret;
}


//----------------Printing Functions Below--------------------//


string Grid::setColor(Tile* tile){
 if (tile->getSearchStat() == FRONTIER){
  return FRONTIERCOLOR;
 }
 if (tile->getSearchStat() == EXPLORED){
  return EXPLOREDCOLOR;
 }
 if (tile->getSearchStat() == PATH){
  return PATHCOLOR;
 }
 else return BASECOLOR;
}

string Grid::setMidLabel(Tile* tile){
  if (tile->getSearchStat() == FAR){
    if (tile->getTerrainType() == WALL){
      return "-WALL-";
    }
    return "";
  }

  else if (tile->getSearchStat() == FRONTIER){
    string str = to_string(tile->getFCost());
    str.resize(6);
    return str;
  }

  else if (tile->getSearchStat() == EXPLORED){
    return "<---->";
  }

  else if (tile->getSearchStat() == PATH){
    return "XXXXXX";
  }

  else return to_string(tile->getXCoord()) +", "+to_string(tile->getYCoord());
}

string Grid::setTopLabel(Tile* tile){
  if (tile->getTerrainType() == BRAMBLE){
    return "*    *";
  }
  else return "";
}

string Grid::setBottomLabel(Tile* tile){
  if (tile->getTerrainType() == BRAMBLE){
    return "*____*";
  }
  else return "______";
}

void Grid::print_grid(){
  string color = BASECOLOR;
  
  cout<<color<<endl<<endl;
  for (int i = 0; i< dimension;i++){
    for (int j = 0; j<dimension;j++){
      color = setColor(tiles_map[dimension-i-1][j]);
      cout <<color<<"|"<<setw(6)<<setTopLabel(tiles_map[dimension-i-1][j])<<"|";
    }
    cout<<endl;
    for (int j = 0; j<dimension;j++){
      color = setColor(tiles_map[dimension-i-1][j]);
      //cout <<color<<"|"<<setw(6)<<to_string(j)+", "+to_string(dimension-i-1)<<"|";
      cout<<color<<"|"<<setw(6)<<setMidLabel(tiles_map[dimension-i-1][j])<<"|";
    }
    cout<<endl;
    for (int j = 0; j<dimension;j++){
      color = setColor(tiles_map[dimension-i-1][j]);
      cout <<color<<"|"<<setw(6)<<setBottomLabel(tiles_map[dimension-i-1][j])<<"|";
    }
    cout<<endl;
  }
  cout<< "\033[0m" <<endl;
}
