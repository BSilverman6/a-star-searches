#include "Grid.h"
#include "Tile.h"
#include "Grid.cpp"
#include "Tile.cpp"


#include <stdlib.h> 
#include <iostream>

using namespace std;

/*Color Codes
Black 0
Red 31
Green 2
Yellow 3
Blue 4
Magenta 5
Cyan 6
White 7
*/
#define RESET   "\033[0m"


int main(){
    Grid* my_grid = new Grid();

    my_grid->setUpMap(9);

    vector <Tile*> short_path = my_grid->getShortestPath(4,0,4,8);
    //my_grid->print_grid();
    cout << "Hello World" << RESET <<endl;
    return 0;
}

