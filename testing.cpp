#include "Grid.h"
#include "Tile.h"
#include "Grid.cpp"
#include "Tile.cpp"


#include <stdlib.h> 
#include <iostream>

using namespace std;

#define RESET   "\033[0m"


int main(){
    Grid* my_grid = new Grid();

    my_grid->setUpMap(9);

    vector <Tile*> short_path = my_grid->getShortestPath(4,0,4,8);
    cout << "Hello World" << RESET <<endl;
    cout << 14*1.5 <<endl;

    return 0;
}

