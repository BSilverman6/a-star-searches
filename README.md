# A* Searches
Final Project for CSPB 2270: Data Structures\
CU Boulder Fall 2024\
Bennett Silverman - Besi9930

On my honor I have neither given nor recieved unauthorized aid. 

## Overview of the Project
The goal of this project was to implement the A* search algorithm - to find the quickest path from A-->B. 

For someone new to A*, the algorithm works by "exploring" tiles based on the sum of two cost - the **G Cost** and the **H Cost**. The **G Cost** is the actual amount of time it takes to get to a tile, and the **H cost** is a hueristic function that calculates the estimated time from that specific tile. The sum of these two is called the **F Cost**.

Each tile on the "Frontier" of the explored terrain has an **F Cost** Calculated based on the known **G cost** of it's neighbor and the **H cost**. As more tiles are explored, these costs are updated to reflect the shortest path already explored to get to. A Priority Queue is used to manage these "Frontier" tiles. Each Tile also stores a pointer to the previous tile used to attain it's own lowest **F Cost**. This way, when the end is found, the pointers can be followed to get back to the start and reveal the shortest path.

The effectiveness of the algorithm depends on *underestimating* the **H cost**. If the **H Cost** is overestimated, then the algorithm may not explore a tile that truly is on the shortest path as the **F Cost** would be diluted (too high) in the pool of "Frontier" tiles". In the Case of Ties, the tile *closest to the end not accounting for obstacles* (lowest **H Cost**) is used as a tiebreaker.

This implementation has a few notes.
* Terrain can slow the time it takes to reach any given tile. Specifically Brambles are twice as slow to travel through as open terrain. This is reflected in the **G_Cost** to reach a tile. 
* Walls cannot be traveled through. Rules for travel in this world also make it such that one cannot travel diagonally across a wall. 

---
In this repository, there are four main parts in this, with respective header files for the first three. Each header files comments contain descriptions of the relevant functions as well as notes on some of the variables. The CPP files are commented to reflect how smaller pieces in each function work/what they do.



1. Grid Class
2. Tile Class
3. PriQu (Priority Queue) Structure
4. Map Generator

The **Grid Class** is responsible for creating a 2 dimensional vector of Tile Pointers. It also contains the functions for printing the grid into 

The **Tile Class** is each unit "tile" in the grid. Each tile also has data relevant to the search algorithm (f_cost, exploration status, etc.) and details for how it fits into the larger grid (Terrain Types, Occupation Status, etc.)

The **PriQue** Structure is modified from our priority queue homework assignment. Aside from modifying it to be used for storing tiles by lowest f-cost ( and within that lowest h-cost)

The **Map Generator** is a handy tool for debugging and visualizing and trying out fun. It contains a main function that can be compiled and run in the terminal. To try it on your own, check out the video walkthrough or keep reading for a brief how-to. 

**NOTE:** The output in the terminal has functionality to ouput colored text that works on my personal Mac OS computer. I have not tested this in other environments, so color may not work if you try it. 

## Video Walkthrough

[A* Searches - Video Supplement (Click Me!)](https://youtu.be/2v_WGBg0s1c)
Note: At 9:30 in the video, i say the tiles have the same f-costs. That isn't the case here! It is in the other direction when the Hero is in the Bottom Left corner.

---
To Create your own map with obstacles, all you have to do is edit a few lines in the map_generator.cpp file. There is a short demo at the end of the video walkthrough.

See the lines of codes with comments on the right in the map_generator.cpp file. There are 7 lines of code that can be changed.

1. **Add your dimension to the set_up_map(X) - 1 line**. This will create and X * X grid of Tiles. I'd reccomend keeping this under 30x30. The priority queue used in the algorithm is fixed right now at 100 (can easily be changed), and we don't want segmentation faults.
2. **Add X,Y, coordinate pairs to the Walls and Brambles vectors - 2 lines** Note that the coordinates are from [0:Dimension), exclusive of the dimension. This will create obstacles that stop or slow the enemy.
3. **Fill in the desired X and Y coordinates for Starting and Ending - 4 lines** The Evil Villian is the starting tile.

4. Now Compile in the command line! I used \
`g++ -std=c++11 map_generator.cpp -o map_generator`

5. `./map_generator` to run your program.

## Reflection
    
### Approach and Challenges
I started this project with a graph of nodes(tiles) with the intent of utilizing an edge class to keep track of the travel time between nodes and which nodes are connected to a given node. In order to utilize these edges I would have to calculate all of them at the start, (ideally) store them in a sorted way, and search them each time i needed to find one that connected to a relevant node. This seemed very inefficient, especially as my maps get bigger.

The benefit of a grid as basis is that each node has neighbors based on **where** it is in the grid. This means that I could use a more efficient algorithm to determine neighbors for a node. The downside is that I'd have to calculate travel times within the algorithm - but this seemed more effective than utilizing the edge class. I changed the class names to Grid and Tile to reflect this change. 

I did a fair bit of research into priority queues and at first settled on using the c++ standard priority queue. The crux of this implementation is the A* algorithm requires me to update the priority of tiles already in the priority queue as i discover new information. At first I decided to add duplicates into the priority queue as thing updated. If a tile was explored when it got to the front of the queue, then I would disregard it and move onto exploring the next. This worked fine, but I noticed a bug where some lower **F Cost** tiles were explored after higher **F Cost** tiles in some odd and very infrequent cases. Ultimately I opted to modify the Priority Queue we made earlier in the class to have an `update_priority` function. Unfortunaly I have to traverse an array in the underlying structure to find a node (O(n)), but it fixed the error I was seeing. 

Originally, I tallied up the `f_cost` as a `float`. This worked fine knowing I didn't need to use the extra memory, but rounding errors were very easy to notice. I then changed this to use `double`, but ran into similar frustrations with rounding errors. Ultimately I decided to use integers multiplied by a factor of 10 - as commonly used in implementing this algorithm. There is some loss of accuracy this way, but it is much cleaner looking and easier to understand.
    

### Next Steps

* One step I would take to improve this project is to Seperate grid class with the printing functionality in a different "Console" Class. This would simply make the Grid Class feel less cluttered and distinguish functions the user can use in a main function. 
* Change the Priority Queue structure to a Class. I personally find it easier to call a function on an object than to pass a structure into a function specifically designed for itself. Personal Preference. 
*Add some kind of dynamic functionality. Can I use inputs in the command line to "Move" the hero around the Grid? Can I have the Enemy follow the path dictated by the algorithm to come "attack" the hero each time the hero moves? This is the start to a very simple video game!


### An Incomplete list of sources


[Sebastion Lague Youtube Video](https://www.youtube.com/watch?v=-L-WgKMFuhE&ab_channel=SebastianLague)\
[Geeks for Geeks](https://www.geeksforgeeks.org/a-search-algorithm/)\
[Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm#)\
Many google searches that led to forums and sites like stackoverflow or c++ help resources - as is typical :)\
Other sources as cited in the my code
