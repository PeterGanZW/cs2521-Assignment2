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
  ItemPQ b = makeNewItem(2,3);
  ItemPQ c = makeNewItem(3,3);
  ItemPQ d = makeNewItem(5,3);
  PQ pq = newPQ();
  int i = PQEmpty(pq);
  printf("%d", i);
  addPQ(pq, a);
  addPQ(pq, b);
  addPQ(pq, c);
  addPQ(pq, d);
  showPQ(pq);
  printf("___________\n");
  ItemPQ e = dequeuePQ(pq);
  showPQ(pq);
  printItem(e);
  dequeuePQ(pq);
  showPQ(pq);
  dequeuePQ(pq);
  showPQ(pq);
  dequeuePQ(pq);
  showPQ(pq);
  freePQ(pq);
  return EXIT_SUCCESS;
}
