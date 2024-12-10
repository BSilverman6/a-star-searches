#include "Grid.h"
#include "Tile.h"
#include "Grid.cpp"
#include "Tile.cpp"


#include <iostream>

using namespace std;

int main(){
    Grid* my_grid = new Grid();

    my_grid->setUpMap(5);

    cout << "Hello World" <<endl;
    return 0;
}