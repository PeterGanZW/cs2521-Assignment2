// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/*
typedef struct PQRep* PQ;
typedef struct ItemPQ {
   int         key;
   int         value;
} ItemPQ;
*/
typedef struct PQNode* PQNode;     // pointer of PQNode

struct PQNode{     // struct of PQNode involves:
    ItemPQ item;   // ItemPQ
    PQNode next   ;// pointer of next PQNode
};

struct PQRep {   // struct of PQRep involves:
    PQNode Head; // pointer of PQNode which treat it as the head 
};

static PQNode newNode(ItemPQ element){
    PQNode new = malloc(sizeof(struct PQNode));// malloc mmemory for PQNode
    new->item = element;                       // update item
    new->next = NULL;                          // set next node ot be NULL
    return new;                                
}

PQ newPQ() {
    PQ new = malloc(sizeof(struct PQRep));     // malloc memory for priority queue
    ItemPQ item;                              // create ItemPQ for PQ
    item.key = -1;
    item.value = -1;
    new->Head = newNode(item);             // update Head
    return new;
}

int PQEmpty(PQ p) {                        // check if PQ is empty
    if (p->Head ==NULL) return 1;          // if TRUE ,return 1;
    return (p->Head->item.key == -1);
}

void addPQ(PQ pq, ItemPQ element) {
    if (PQEmpty(pq)){                      // if PQ is empty
        pq->Head->item = element;          // update head
        return;
    }
    PQNode tmp = pq->Head;                 
    while (tmp->next!=NULL){               // go to the lastest node
        tmp = tmp->next;
    }
    PQNode new = newNode(element);         // insert it after the latest node
    tmp->next = new;
}

static void deleteNode(PQ pq, PQNode node){
    if (pq->Head == node) {                // if head is the node which we want to delete
        PQNode tmp = pq->Head;
        pq->Head = tmp->next;
        free(tmp);
    } else {                               // if not
        PQNode tmp = pq->Head;
        while(tmp->next!=node){            // find the node
            tmp = tmp->next;
        }
        PQNode del = tmp->next;            // delete the node
        tmp->next = tmp->next->next;
        free(del);
    }
}

ItemPQ dequeuePQ(PQ pq) {
    ItemPQ throwAway = {};                 // create item called throwaway 
    throwAway.value = -1;
    throwAway.key = -1;
    if (PQEmpty(pq)) {                     // if PQ is empty
        return throwAway;                  // return NULL
    }
    PQNode smallest = pq->Head;            
    PQNode tmp = smallest;
    while(tmp->next!=NULL){                // go through the PQ
        if (tmp->next->item.value < smallest->item.value) 
            {                              // update smallest if finf smaller value
                smallest = tmp->next;
            }
        tmp = tmp->next;
    }
    throwAway = smallest->item;            
    deleteNode(pq, smallest);              // delete smallest
    return throwAway;
}


void updatePQ(PQ pq, ItemPQ element) {
    if (PQEmpty(pq)) return;               // PQ is not empty
    PQNode tmp = pq->Head;
    while (tmp!=NULL) {                    // //traverse all nodes to find the key.
        if (tmp->item.key == element.key){
            tmp->item.value = element.value;
            return;
        } 
        tmp = tmp->next;
    }
}

void showPQ(PQ pq) {
    PQNode tmp = pq->Head;
    while (tmp != NULL){                     // show the priority queue
        printf("ITEM KEY: %d VALUE %d\n", tmp->item.key, tmp->item.value);
        tmp = tmp->next;
    }
}

void  freePQ(PQ pq) {
    if (PQEmpty(pq)) return;                 
    PQNode tmp = pq->Head;
    PQNode prev = tmp;
    while(tmp!=NULL){                        // free all nodes 
        tmp = tmp->next;
        free(prev);
        prev = tmp;
    }
}
