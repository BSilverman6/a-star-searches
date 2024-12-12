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
    vector <int> walls = {5,3,5,4,5,5,5,6,5,7,6,3,6,7,7,3,7,4};
    vector <int> brambles = {1,1, 2,1, 3,1, 4,2, 4,3, 4,4, 4,5, 4,6, 4,7, 4,8, 4,9,5,0,5,1,5,2,6,0,6,1,6,2,6,5,6,6,7,5,7,6,8,4,8,5};
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 6;
    int s_y = 4;
    int e_x = 0;
    int e_y = 0;

    my_grid->addCharacters(s_x,s_y, e_x,e_y);
    vector <Tile*> short_path = my_grid->getShortestPath(s_x,s_y, e_x,e_y);
    for (auto v: short_path){
        cout<<"("<<v->getXCoord()<<","<<v->getYCoord()<<")"<<endl;;
    }
    cout<<"Hooray!"<<endl;

    return 0;
}

