#include "Grid.h"
#include "Tile.h"
#include "PriQu.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <string>


using namespace std;

/* Note that All Print related functions are at 
the bottom of this file the rest can be found in
the order of the .h file.*/

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

}


vector <Tile*>  Grid::getShortestPath(int sx, int sy, int ex, int ey){
  //identifies starting and ending tiles based on cartesian coordinates
  Tile* start = tiles_map[sy][sx];
  Tile* end = tiles_map[ey][ex];
  
  print_grid();

  //Updates the relevant first tile search states
  start->setGCost(0);

  //initialize the priority queue and set's the 
  //"cursor" Tile.
  pq* frontier_pq = new pq;
  Tile* current_tile = start; 

  //This is the bulk of the algorithm
  //Get's and Updates (if needed) the neighbor(s) of the "cursor"
  //Updates include: h_cost, g_cost, f_cost (calculated in setCost()), and
    //a pointer to the current tile for path record keeping purposes
  do{
    //current Tile set to Explored
    current_tile->setSearchStat(EXPLORED);

    set <Tile*> neighbors = getValidNeighbors(current_tile);
    for (auto n: neighbors){
      int n_search_stat = n->getSearchStat();
      if (n_search_stat != EXPLORED){
        
        int h_cost = calc_h_cost(n, end);
        int g_cost = current_tile->getGCost()+calc_travel_time(current_tile, n);

        //Adds/updates the Priority Queue if this neighbor is a newly explored tile OR if a better path was found.
        //adds the newly frontiered tile to the pqueue
        //duplicates updated;
        if (n_search_stat == FAR){
          n->setCosts(h_cost,g_cost,current_tile);
          insert_pq(frontier_pq, n);
        }
        if (n_search_stat == FRONTIER && n->getFCost()> h_cost+g_cost){
          n->setCosts(h_cost,g_cost,current_tile);
          update_priority_pq(frontier_pq, n);
        }
      }
    }


    current_tile = remove_pq(frontier_pq);

    print_grid();

  //loop ends when endgoal discovered or everything accessible is explored
  }while (current_tile !=end  && current_tile !=nullptr);

  delete frontier_pq; //free the heap (memory)!
  
  //returns the path to the end goal as a vector - or an empty vector if goal not found
  vector <Tile*> shortest_path;
  if (current_tile == end){
    Tile* path_tile = current_tile;
    shortest_path.push_back(path_tile);
    path_tile->setSearchStat(PATH);
    do{
      path_tile = path_tile->getLastVisited();
      shortest_path.push_back(path_tile);
      path_tile->setSearchStat(PATH);

    } while(path_tile != start);
  }

  print_grid();

  //Clears the Search Status of everything
  for(auto v: tiles_map){
    for (auto t: v){
      t->clearSearchStatus();
    }
  }

  print_grid();
  
  return shortest_path;
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


//works based on printed numbers in printed Visual!
int Grid::calc_travel_time (Tile* current, Tile* neighbor){
  //2 fields
  double modifier = 1.0;
  int distance = 10;

  if ((current->getTerrainType() == BRAMBLE && neighbor->getTerrainType() == FIELD)
      || (current->getTerrainType() == FIELD && neighbor->getTerrainType() == BRAMBLE)){
      modifier = 1.5;
  }
  if (current->getTerrainType() == BRAMBLE && neighbor->getTerrainType() == BRAMBLE){
      modifier = 2.0;
  }

  if (current->getXCoord() != neighbor->getXCoord() && current->getYCoord() != neighbor->getYCoord()){
    distance = 14;
  }

  int ret = modifier*distance;
  ret = round(ret*100)/100;
  return ret;
}



int Grid::calc_h_cost(Tile* tile, Tile* end){
  int t_x = tile->getXCoord();
  int t_y = tile->getYCoord();
  int e_x = end->getXCoord();
  int e_y = end->getYCoord();
  int dx = abs(t_x - e_x);
  int dy = abs(t_y - e_y);
  
  int dist = (dx+dy)*10+(14-(20))*min(dx,dy);
  return dist;
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
  if (tile->getTerrainType() == BRAMBLE && tile->getOccupiedStat() != EMPTY){
    if(tile->getOccupiedStat() == START){
      return "*STAR*";
    }
    else return "*END!*";
  }
  
  else if (tile->getTerrainType() == BRAMBLE){
    return "*____*";
  }

  else if (tile->getOccupiedStat() == END){
    return "_Hero_";
  }

  else if (tile->getOccupiedStat() == START){
    return "_EVIL_";
  }
  else return "______";

}

void Grid::addCharacters(int sx, int sy, int ex, int ey){
  tiles_map[sy][sx]->setOccupiedStat(START);
  tiles_map[ey][ex]->setOccupiedStat(END);
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
  cout<< RESET <<endl;
}
