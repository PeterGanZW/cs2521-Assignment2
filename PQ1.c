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
BSTNode BSTreeInsert(BSTree t, ItemPQ element){
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
	return (p->root== NULL);
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
}// delete root of tree
static
BSTree deleteRoot(BSTree t)
{
    // if no subtrees, tree empty after delete
    if (t->left == NULL && t->right == NULL) {
        free(t);
        return NULL;
    }
    // if only right subtree, make it the new root
    else if (t->left == NULL && t->right != NULL) {
        free(t);
        return t->right;
    }
    // if only left subtree, make it the new root
    else if (t->left != NULL && t->right == NULL) {
        free(t);
        return t->left;
    }
    // else (t->left != NULL && t->right != NULL)
    // so has two subtrees
    // - find inorder successor
    // - move its value to root
    // - delete inorder successor node
    BSTLink parent = t;
    BSTLink succ = t->right; // not null!
    while (succ->left != NULL) {
        parent = succ;
        succ = succ->left;
    }
    t->element = succ->element;
    free(succ);
    if (parent == t)
        parent->right = NULL;
    else
        parent->left = NULL;
    return t;
}

// delete a value from a BSTree
static BSTree BSTreeDelete(BSTree t,ItemPQ element)
{
    if (t == NULL)
        return NULL;
    else if (element.value < t->element.value)
        t->left = BSTreeDelete(t->left, element);
    else if (element.value >= t->element.value && element.key!=t->element.key)
        t->right = BSTreeDelete(t->right, element);
    else // (v == t->value)
        t = deleteRoot(t);
    return t;
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
    //printf("THE NODE HAS BEEN FOUND key: %d, value:%d\n", node->element.key, node->element.value);
    //remove the node
    if (node!=NULL) {
    pq->root = BSTreeDelete(pq->root, element);
    //reinsert the new element into tree.
    pq->root = BSTreeInsert(pq->root, element);
    }
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
    assert(pq!=NULL);
    printBSTree(pq->root);
    printf("___________\n");
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


