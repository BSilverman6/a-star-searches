#ifndef GRID_H__
#define GRID_H__

#include "Tile.h"
#include <queue>
#include <set>
#include <vector>

#define FIELD_FIELD 10
#define BRAMBLE_BRAMBLE 11
#define FIELD_BRAMBLE 12

/*Mac Based Terminal Colors
Color Codes
Black 0
Red 1
Green 2
Yellow 3
Blue 4
Magenta 5
Cyan 6
White 7

I Used a lot of sources to find these, most of which were
semi-relevant forums found through google
Unfortunately, I can't find the first one I used that was good
but here are two others.
https://stackoverflow.com/questions/33309136/change-color-in-os-x-console-output
https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
*/
#define BASECOLOR "\x1b[40;37;1m" //white
#define FRONTIERCOLOR "\x1b[40;31;1m" //Red
#define EXPLOREDCOLOR "\x1b[40;36;1m" //Cyan
#define PATHCOLOR "\x1b[40;33;1m" //Yellow
#define RESET   "\x1b[0m"



//The Priority Queue for picking which frontier tile
//to explore next in the search algorithm
typedef priority_queue <Tile*, vector<Tile*>, Tile> a_star_queue;

using namespace std;


class Grid {
public:
  Grid();
  ~Grid();

  //returns the 2D Vector of Tiles*
  //access a tile by [y][x] coordinates
  vector<vector<Tile*>> getTiles();

  //sets up a blank square grid with the specified dimension
  //indices are 0:dimension-1
  void setUpMap(int dimension);

  /* The A* Search Algorithm!
  Returns a vector of Tiles* that has the shortest pathfrom Sx,Sy to Ex,Ey
  The return vector is sorted End Tile* --> Start Tile* 
  Returns empty if no path was found*/
  vector <Tile*> getShortestPath(int sx, int sy, int ex, int ey);


  //Prints the Grid in a visual Way :)
  //Great for Debugging.
  void print_grid();
  
  //Added for Final Visuals
  void addCharacters(int sx, int sy, int ex, int ey);

  
private:

  //The size of the Grid
  int dimension;

  //The 2d Vector of the Map
  //access a tile by [y][x] coordinates
  vector<vector<Tile*>> tiles_map;

  //Get's the Valid Neighbors (FIELD and BRAMBLE)
  //of a Given Tile. Excludes Walls, Out of Bound Indices
  //and Diagonals across a corner.
  //Returns a set <Tile*>.
  set <Tile*> getValidNeighbors (Tile* my_Tile);

  //Calculates the Travel Time Between 2 Points
  //Bramble <-->Field is 1.5 Times slower
  //Tile <--> Corner is 1.4 Times Slower
  //Bramble <--> Bramble is 2 Times Slower
  //Terrain based tile location based modifiers stack.
  int calc_travel_time (Tile* current, Tile* neighbor);
  
  //Heuristic for determining the distance to the End Point
  //adapted from Diagonal Distance https://www.geeksforgeeks.org/a-search-algorithm/
  //originally I used the cartesian formula distance between 2 points.
  int calc_h_cost(Tile* tile, Tile* end);

  //The Following are for Grid Visuals
  //Great for Debugging!
  string setColor(Tile* tile);
  string setMidLabel(Tile* tile);
  string setTopLabel(Tile* tile);
  string setBottomLabel(Tile* tile);
};



#endif // GRID_H__

//Final Commit!