#ifndef PRIQU_H__
#define PRIQU_H__

#include <memory>
#include "Tile.h"
using namespace std;

// adpated from our Priority Queue Homework

//low f-cost is more priority
//lower h-cost is more priority (tiebreaker)


#define INITIAL_PQ_CAPACITY 100
struct pq {
  Tile* active_frontiers[INITIAL_PQ_CAPACITY];
  int capacity = INITIAL_PQ_CAPACITY;
  int size = 0;
  
};


pq* init_pri_qu();

// peek_pq will access the highest priority element in the queue and return it
// without modifying the queue. If the queue is empty it should return the empty
// string.
Tile* peek_pq(pq*& queue);

// insert_pq adds the given string to the queue, using the f and h costs of the tile
// If there is a tie, the given string should be placed at the back of the group
// that it ties with, so all other strings with this priority will be removed
// first.
void insert_pq(pq*& queue, Tile* tile);

// remove_pq will access the highest priority element in the queue, remove it
// from the queue, and return it. If the queue is empty it should return 
// nullptnr
Tile* remove_pq(pq*& queue);

//Swaps two indices in a given queue's the_queue
void swap (pq*& queue, int s, int w);

//percolates the selected index up
void percolate_up (pq*& queue, int young_index);

//percolates the selected index down. Prioritizes swapping
//with the higher priority child index.
void percolate_down(pq*& queue, int high_index);

//compares two indicies in the heap structure
int get_high_pr_index (pq* queue, int index_1, int index_2);

//When the f_cost of a FRONTIER tile is updated, Call This.
//SEARCHES (O(n)) for the updated Tile
//Then Percolates the updated Tile Up.
void update_priority (pq*& queue, Tile* tile);

#endif // PRIORITYQUEUE_H__
