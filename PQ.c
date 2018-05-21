// PQ ADT interface for Ass2 (COMP2521)
// Have used source code of BSTree in lab-17
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
typedef struct PQRep *PQ;
typedef struct ItemPQ {
   int         key;
   int         value;
} ItemPQ;
*/
typedef struct BSTNode *BSTNode;
typedef struct BSTNode *BSTLink;
struct BSTNode {
    ItemPQ element;
    BSTLink left, right;
};

typedef struct BSTNode *BSTree;
// make a new node containing a value
struct PQRep {
    BSTree root;
};

static
BSTLink newBSTNode(ItemPQ element)
{
    BSTLink new = malloc(sizeof(struct BSTNode));
    assert(new != NULL);
    new->element = element;
    new->left = new->right = NULL;
    return new;
}
static
void BSTreeInsert(BSTree t, ItemPQ element){
    if (element.value < t->element.value) {
        if (t->left != NULL){
            BSTreeInsert(t, element);
        } else {
            t->left = newBSTNode(element);
        }
    } else {
        if (t->right != NULL){
            BSTreeInsert(t, element);
        } else {
            t->right = newBSTNode(element);
        }
    }
}

PQ newPQ(){
    PQ new = (PQ)malloc(sizeof(struct PQRep));
    new -> root = NULL;
    return new;
}

int PQEmpty(PQ p) {
	return (p== NULL);
}

void addPQ(PQ pq, ItemPQ element) {
    if (pq->root == NULL){
        pq->root = newBSTNode(element);
    } else {
        BSTreeInsert(pq->root, element);
    }
}

//find the parent of smallest node
static BSTree parentOfSmallest(BSTree t){
    if (t->left->left !=NULL)
        return parentOfSmallest(t->left);
    else 
        return t;
}

ItemPQ dequeuePQ(PQ pq) {
    BSTNode parent = parentOfSmallest(pq->root);
    BSTNode child = parent->left;
    BSTNode grandchild = child->right;
	ItemPQ throwAway = child->element;
    free(child);
    parent->left = grandchild;
	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {
   /* BSTNode node = findNode(pq->root, element);
    if (node == NULL) return;
    node->element*/
}

BSTNode findNode(BSTree t, ItemPQ element){
    if (t==NULL) return NULL;
    if (t->element.key == element.key){
        return t;
    } else if (t->element.value < element.value){
        return findNode(t->left,element);
    } else {
        return findNode(t->right,element);
    }
}

void printBSTree(BSTree t){
    if (t!= NULL){
        printf("Key: %d Value: %d\n",t->element.key,t->element.value);
        if (t->left!=NULL){
            printf("left Side of key: %d\n", t->element.key);
            printBSTree(t->left);
        } 
        if (t->right!=NULL){
            printf("Right Side of key: %d\n", t->element.key);
            printBSTree(t->right);
        }
    }
}

void showPQ(PQ pq) {
    printBSTree(pq->root);
}

void freeTree(BSTree t){
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

void freePQ(PQ pq) {
    freeTree(pq->root);
    free(pq);
}


