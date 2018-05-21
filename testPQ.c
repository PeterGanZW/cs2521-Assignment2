#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

ItemPQ makeNewItem(int key, int value){
    ItemPQ pq;
    pq.key = key;
    pq.value = value;
    return pq;
}
int main(){
  ItemPQ a = makeNewItem(1,2);
  ItemPQ b = makeNewItem(2,2);
  ItemPQ c = makeNewItem(3,3);
  PQ pq = newPQ();
  addPQ(pq, a);
  //addPQ(pq, b);
  addPQ(pq, c);
  showPQ(pq);
  return EXIT_SUCCESS;
}
