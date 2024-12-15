
#include "Grid.cpp"
#include "Tile.cpp"
#include "PriQu.cpp"


#include <iostream>

using namespace std;



int main(){
    Grid* my_grid = new Grid();

    //Tutorial!
    my_grid->setUpMap(5); //change this to change the dimension
    vector <int> walls = {2,1,2,2,2,3}; //Use X, Y pairs based on the square dimension above. Axes run from [0:Dimension-1]
    vector <int> brambles = {0,1,0,3,1,1,1,3,3,2,4,2 }; //again, x,y,   x2,y2... pairs
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 2; // Input Starting X Y coordinates (for the Villain)
    int s_y = 4; // update
    int e_x = 2; //Input Ending X Y coordinates (for the Hero)
    int e_y = 0; //update
    my_grid->addCharacters(s_x,s_y, e_x,e_y); 


    //Level Dead End Case
    /* my_grid->setUpMap(5);
    vector <int> walls = {0,2,1,2,2,2,3,2,4,2};
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    int s_x = 0;
    int s_y = 0;
    int e_x = 4;
    int e_y = 4;
    my_grid->addCharacters(s_x,s_y, e_x,e_y); */
    

    //Level Bramble
    /* my_grid->setUpMap(10);
    vector <int> walls = {0,4,0,5};
    vector <int> brambles = {
    0,1,1,1,2,1,3,1,4,  1,6,1,7,1,8,1,9,1,  
    0,2,1,2,2,2,3,2,4,  2,6,2,7,2,8,2,9,2,  
    0,3,1,3,2,3,3,3,4,  3,6,3,7,3,8,3,9,3, 
        1,4,2,4,3,4,4,  4,6,4,7,4,8,4,9,4,
        1,5,2,5,3,5,4,  5,6,5,7,5,8,5,9,5,
    0,6,1,6,2,6,3,6,4,  6,6,6,7,6,8,6,9,6,
    0,7,1,7,2,7,3,7,4,  7,6,7,7,7,8,7,9,7,
    0,8,1,8,2,8,3,8,4,  8,6,8,7,8,8,8,9,8
    };
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 0;
    int s_y = 0;
    int e_x = 0;
    int e_y = 9;
    my_grid->addCharacters(s_x,s_y, e_x,e_y); */
    

    // Level 3 Puzzle (see the algorithm )
    /* my_grid->setUpMap(10);
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
    my_grid->addCharacters(s_x,s_y, e_x,e_y);  */


    //Level 2 Puzzle (Comment out 9,4,)
    /* my_grid->setUpMap(20);
    vector <int> walls = {4,6,4,7, 4,8, 4,9,  9,4,  9,5,9,6,9,7,10,8,11,9,12,10};
    vector <int> brambles = {};
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 0;
    int s_y = 7;
    int e_x = 19;
    int e_y = 7;
    my_grid->addCharacters(s_x,s_y, e_x,e_y); */

    //Level 1 Puzzle
   /*  my_grid->setUpMap(10);
    vector <int> walls = {0,2,1,2,2,2,3,2,4,2,5,2,7,2,8,2,9,2,  0,5,1,5,2,5,4,5,5,5,6,5,7,5,8,5,9,5,    0,7,1,7,2,7,3,7,4,7,6,7,7,7,8,7,9,7};
    vector <int> brambles = {};
    for (int i = 0; i<walls.size(); i=i+2){
        my_grid->getTiles()[walls[i+1]][walls[i]]->setTerrainType(WALL);
    }
    for (int i = 0; i<brambles.size(); i=i+2){
        my_grid->getTiles()[brambles[i+1]][brambles[i]]->setTerrainType(BRAMBLE);
    } 
    int s_x = 4;
    int s_y = 0;
    int e_x = 9;
    int e_y = 9;
    my_grid->addCharacters(s_x,s_y, e_x,e_y); */


    vector <Tile*> short_path = my_grid->getShortestPath(s_x,s_y, e_x,e_y);
    for (auto v: short_path){
        cout<<"("<<v->getXCoord()<<","<<v->getYCoord()<<")"<<endl;;
    }
    cout<<"Hooray!"<<endl;

    return 0;

    //FInal Commit!
}

