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
typedef struct PQNode* PQNode;

struct PQNode{
    ItemPQ item;
    PQNode next;
};

struct PQRep {
    PQNode Head;
};

static PQNode newNode(ItemPQ element){
    PQNode new = malloc(sizeof(struct PQNode));
    new->item = element;
    new->next = NULL;
    return new;
}

PQ newPQ() {
    PQ new = malloc(sizeof(struct PQRep));
    ItemPQ item;
    item.key = -1;
    item.value = -1;
    new->Head = newNode(item);
    return new;
}

int PQEmpty(PQ p) {
    if (p->Head ==NULL) return 1;
    return (p->Head->item.key == -1);
}

void addPQ(PQ pq, ItemPQ element) {
    if (PQEmpty(pq)){
        pq->Head->item = element;
        return;
    }
    PQNode tmp = pq->Head;
    while (tmp->next!=NULL){
        tmp = tmp->next;
    }
    PQNode new = newNode(element);
    tmp->next = new;
}

static void deleteNode(PQ pq, PQNode node){
    if (pq->Head == node) {
        PQNode tmp = pq->Head;
        pq->Head = tmp->next;
        free(tmp);
    } else {
        PQNode tmp = pq->Head;
        while(tmp->next!=node){
            tmp = tmp->next;
        }
        PQNode del = tmp->next;
        tmp->next = tmp->next->next;
        free(del);
    }
}

ItemPQ dequeuePQ(PQ pq) {
    ItemPQ throwAway = {};
    throwAway.value = -1;
    throwAway.key = -1;
    if (PQEmpty(pq)) {
        return throwAway;
    }
    PQNode smallest = pq->Head;
    PQNode tmp = smallest;
    while(tmp->next!=NULL){
        if (tmp->next->item.value < smallest->item.value) 
            {
                smallest = tmp->next;
            }
        tmp = tmp->next;
    }
    throwAway = smallest->item;
    deleteNode(pq, smallest);
    return throwAway;
}


void updatePQ(PQ pq, ItemPQ element) {
    if (PQEmpty(pq)) return;
    PQNode tmp = pq->Head;
    while (tmp!=NULL) {
        if (tmp->item.key == element.key){
            tmp->item.value = element.value;
            return;
        } 
        tmp = tmp->next;
    }
}

void showPQ(PQ pq) {
    PQNode tmp = pq->Head;
    while (tmp != NULL){
        printf("ITEM KEY: %d VALUE %d\n", tmp->item.key, tmp->item.value);
        tmp = tmp->next;
    }
}

void  freePQ(PQ pq) {
    if (PQEmpty(pq)) return;
    PQNode tmp = pq->Head;
    PQNode prev = tmp;
    while(tmp!=NULL){
        tmp = tmp->next;
        free(prev);
        prev = tmp;
    }
}
