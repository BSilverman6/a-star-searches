#include "Grid.h"
#include "Tile.h"
#include "Grid.cpp"
#include "Tile.cpp"


#include <stdlib.h> 
#include <iostream>

using namespace std;



int main(){
    Grid* my_grid = new Grid();

    my_grid->setUpMap(10);
    vector <int> walls = {4,4,4,5,5,4,5,5};
    vector <int> brambles = {3,3,3,4, 3,5,3,6, 4,6,5,6, 6,6,6,5, 6,4,6,3, 5,3,4,3};
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 0;
    int s_y = 0;
    int e_x = 9;
    int e_y = 9;

    my_grid->addCharacters(s_x,s_y, e_x,e_y);
    vector <Tile*> short_path = my_grid->getShortestPath(s_x,s_y, e_x,e_y);
    for (auto v: short_path){
        cout<<"("<<v->getXCoord()<<","<<v->getYCoord()<<")"<<endl;;
    }
    cout<<"Hooray!"<<endl;

    return 0;
}

