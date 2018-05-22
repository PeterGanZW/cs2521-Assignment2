#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

ItemPQ makeNewItem(int key, int value){
    ItemPQ pq;
    pq.key = key;
    pq.value = value;
    return pq;
}
void printItem(ItemPQ item){
    printf("key: %d, value:%d\n", item.key, item.value);
}
int main(){
  ItemPQ a = makeNewItem(1,3);
  ItemPQ b = makeNewItem(2,4);
  ItemPQ c = makeNewItem(3,2);
  ItemPQ d = makeNewItem(5,1);
  PQ pq = newPQ();
  addPQ(pq, a);
  addPQ(pq, b);
  addPQ(pq, c);
  addPQ(pq, d);
  a = makeNewItem(1, 10);
  updatePQ(pq,a);
  b = makeNewItem(1, 1);
  updatePQ(pq,b);
  showPQ(pq);
  return EXIT_SUCCESS;
}
