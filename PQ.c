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
BSTree BSTreeInsert(BSTree t, ItemPQ element){
    /*if (element.value < t->element.value) {
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
    }*/
    if (t == NULL)
        return newBSTNode(element);
    else if (element.value < t->element.value)
        t->left = BSTreeInsert(t->left, element);
    else 
        t->right = BSTreeInsert(t->right, element);
    return t;
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
    pq->root = BSTreeInsert(pq->root, element);
}

//find the parent of smallest node
static BSTree parentOfSmallest(BSTree t){
    assert(t!=NULL);
    if (t->left == NULL) return t;
    if (t->left->left !=NULL)
        return parentOfSmallest(t->left);
    else 
        return t;
}

ItemPQ dequeuePQ(PQ pq) {
    assert(pq!=NULL);
    ItemPQ throwAway;
    throwAway.value = 0;
    throwAway.key = 0;
    if (pq->root == NULL) return throwAway;
    BSTNode parent = parentOfSmallest(pq->root);
    if (parent->left == NULL){//the smallest is the root
        throwAway = parent->element;
        pq->root = parent->right;
        free(parent);
        return throwAway;
    } else {
        BSTNode child = parent->left;
        BSTNode grandchild = child->right;
	    throwAway = child->element;
        free(child);
        parent->left = grandchild;
    }
	return throwAway;
}
BSTNode static minValueNode(BSTree t){
    if (t->left != NULL){
        return minValueNode(t->left);
    } else {
        return t;
    }
}
static
void deleteNode(BSTNode node){
    // // node with only one child or no child
    if (node->left == NULL){
        node = node -> right;
    } else if (node->right == NULL){
        node = node -> left;
    } else {
    //has two children, get the smallest children in the right tree
    BSTNode temp = minValueNode(node->right);
    node->element = temp->element; //replace the current node's element with the succcessor
    deleteNode(temp);
    }
}

//given a key, find the node inside the tree.
static BSTNode findNode(BSTree t, int key) {
    if (t!= NULL){
        if (t->element.key == key){
            return t;
        } else {
            BSTNode foundNode = findNode(t->left, key);
            if (foundNode == NULL){
                foundNode = findNode(t->right, key);
            }
            return foundNode;
        }
    } else {
        return NULL;
    }
}
void updatePQ(PQ pq, ItemPQ element) {
    BSTNode node = findNode(pq->root, element.key);//traverse all nodes to find the key.
    printf("THE NODE HAS BEEN FOUNDkey: %d, value:%d\n", node->element.key, node->element.value);
    //remove the node
    deleteNode(node);
    //reinsert the new element into tree.
    BSTreeInsert(pq->root, element);
}



/*BSTNode findNode(BSTree t, ItemPQ element){
    if (t==NULL) return NULL;
    if (t->element.key == element.key){
        return t;
    } else if (t->element.value < element.value){
        return findNode(t->left,element);
    } else {
        return findNode(t->right,element);
    }
}*/

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


