#include "PriQu.h"

#include <iostream>
using namespace std;
// Implement this after defining struct in .h file
pq* init_priority_queue() {
  pq* my_pq(new pq);
  return my_pq;
}

Tile* peek_pq(pq*& queue) {
  if (queue->size == 0){
    return nullptr;
  }
  else return queue->active_frontiers[0];
}

void insert_pq(pq*& queue, Tile* tile){
  queue->active_frontiers[queue->size] = tile;
  queue->size++;

  percolate_up (queue, queue->size-1);
}

Tile* remove_pq(pq*& queue) {
  swap (queue, 0, queue->size-1);
  queue->size--;

  percolate_down (queue, 0);

  //copies the Tile* removed.
  Tile* the_tile = queue->active_frontiers[queue->size];

  //resets the node at the spot
  queue->active_frontiers[queue->size] = nullptr;

  return the_tile;
}

void swap (pq*& queue, int s, int w){
  Tile* temp = queue->active_frontiers[s];
  queue->active_frontiers[s] = queue->active_frontiers[w];
  queue->active_frontiers[w] = temp;
}

void percolate_up (pq*& queue, int young_index){
  if (young_index>0) {
    //if node is greater priority, swap index and parent
    //call percolate_up on parent
    int parent_index = (young_index-1)/2;
    if (queue->active_frontiers[young_index]->getFCost() < queue->active_frontiers[parent_index]->getFCost()
        || (queue->active_frontiers[young_index]->getFCost() == queue->active_frontiers[parent_index]->getFCost()
        && queue->active_frontiers[young_index]->getHCost() < queue->active_frontiers[parent_index]->getFCost())){
      swap (queue, young_index, parent_index);
      percolate_up(queue, parent_index);
    }
    
  }

}

void percolate_down(pq*& queue, int top_index){
  Tile* high_node = queue->active_frontiers[0];
  int ch1_index = (top_index*2)+1;
  int ch2_index = (top_index*2)+2;
  int num_children = 0;

  //
  if (queue->size-1 >= ch1_index){
    num_children++;
  }
  if (queue->size-1 >= ch2_index){
    num_children++;
  }
  
  if (num_children == 2){
    int higher_pr_child_index = get_high_pr_index (queue, ch1_index, ch2_index);
    int highest_pr_of_3 = get_high_pr_index (queue, top_index, higher_pr_child_index);

    //if the highest priority is a child, swap with top index with child, percolate down the child
    if (highest_pr_of_3 == higher_pr_child_index){
      swap (queue, top_index, higher_pr_child_index);
      percolate_down (queue, higher_pr_child_index);
    }
  }

  else if (num_children == 1){
    int highest_pr_of_2 = get_high_pr_index (queue, top_index, ch1_index);

    if (highest_pr_of_2 == ch1_index){
      swap (queue, top_index, ch1_index);
      percolate_down (queue, ch1_index);
    }
  }
  

  //there is only 1 child, checks priority and swaps

  //has one child

  //has two children

  //has no children, does nothing more

}

int get_high_pr_index (pq* queue, int index_1, int index_2){
    if (queue->active_frontiers[index_1]->getFCost() < queue->active_frontiers[index_2]->getFCost()){
      return index_1;
    }
    else if (queue->active_frontiers[index_1]->getFCost() > queue->active_frontiers[index_2]->getFCost()){
      return index_2;
    }
    //the two priorities are equal, look at HCost
    else if (queue->active_frontiers[index_1]->getHCost() < queue->active_frontiers[index_2]->getHCost()){
      return index_1;
    }
    else return index_2;
  }

void update_priority (pq*& queue, Tile* tile){
  for (int i = 0; i<queue->size; i++){
    if (queue->active_frontiers[i] == tile){
      percolate_up(queue, i);
      return;
    }
  }
}

//Parent is (i-1)/2
//children are (i*2)+1 and (i*2)+2