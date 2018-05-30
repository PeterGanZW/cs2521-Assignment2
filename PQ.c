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
typedef struct BSTNode *BSTLink;      // pointer of BSTNode
struct BSTNode {                      // struct of BSTNode involves:
    ItemPQ element;                   // ItemPQ
    BSTLink left, right;              // pointer of left and right BSTNode
};

typedef struct BSTNode *BSTree;       // pointer of BSTNode
// make a new node containing a value
struct PQRep {                        // struct of PQRep involves:
    BSTree root;                      // pointer of BSTNode which treat it as the root of the BST 
};

static BSTLink newBSTNode(ItemPQ element) {      
    BSTLink new = malloc(sizeof(struct BSTNode)); // malloc mmemory for BSTNode
    assert(new != NULL);                         
    new->element = element;                       // update element
    new->left = new->right = NULL;                // set left and right node to be NULL
    return new;                                   // return pointer new BSTNode 
}

static BSTNode BSTreeInsert(BSTree t, ItemPQ element){
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
    if (t == NULL)                                  // create a new BSTNode if t is NULL
        return newBSTNode(element);
    else if (element.value < t->element.value)      // use recursion to find the right position and insert in the BST
        t->left = BSTreeInsert(t->left, element);
    else 
        t->right = BSTreeInsert(t->right, element);
    return t;                                       // return the new BSTree which involves inserted element
}

PQ newPQ(){
    PQ new = (PQ)malloc(sizeof(struct PQRep));      // malloc memory for priority queue
    new -> root = NULL;                             // set root to be NULL
    return new;                                     // return new priority queue
}

int PQEmpty(PQ p) {                                 // check if PQ is empty
	return (p== NULL);                              // if TRUE ,return 1; else, return 0
}

void addPQ(PQ pq, ItemPQ element) {                
    pq->root = BSTreeInsert(pq->root, element);     // insert element using BSTreeInsert function
}

//find the parent of smallest node
static BSTree parentOfSmallest(BSTree t){
    assert(t!=NULL);                                // assert t is not NULL
    if (t->left == NULL) return t;                  // t is parent if t->left is NULL          
    if (t->left->left !=NULL)                       // else, use recursion to find the parent
        return parentOfSmallest(t->left);
    else 
        return t;
}

ItemPQ dequeuePQ(PQ pq) {
    assert(pq!=NULL);                            // assert pq is not NULL
    ItemPQ throwAway;                            // create item called throwaway
    throwAway.value = 0;
    throwAway.key = 0;
    if (pq->root == NULL) return throwAway;      // if root is NULL return NULL item
    BSTNode parent = parentOfSmallest(pq->root); // find the parent of smallest node
    if (parent->left == NULL){                   // the smallest is the root
        throwAway = parent->element;             // update throwaway
        pq->root = parent->right;                // update the root
        free(parent);                            // free the parent
        return throwAway;                        // end function
    } else {                                     // the smallest is not the root
        BSTNode child = parent->left;            // child is the right node of parent
        BSTNode grandchild = child->right;       // grandchild is the right node of child
	    throwAway = child->element;              // update throwaway
        free(child);                             // free the child
        parent->left = grandchild;               // update the PQ
    }
	return throwAway;                            // return throwAway
}

// delete root of tree
static BSTree deleteRoot(BSTree t){
    if (t->left == NULL && t->right == NULL) {       // if no subtrees, tree empty after delete
        free(t);
        return NULL;
    }else if (t->left == NULL && t->right != NULL) { // if only right subtree, make it the new root
        free(t);
        return t->right;
    }else if (t->left != NULL && t->right == NULL) { // if only left subtree, make it the new root
        free(t);
        return t->left;
    }
    BSTLink parent = t;              // else (t->left != NULL && t->right != NULL)
    BSTLink succ = t->right;         // so has two subtrees 
    while (succ->left != NULL) {  
        parent = succ;               // - find inorder successor
        succ = succ->left;
    }
    t->element = succ->element;  
    free(succ);                      // - delete inorder successor node
    if (parent == t)
        parent->right = NULL;
    else
        parent->left = NULL;
    return t;                        // return the new BSTree t
}

// delete a value from a BSTree
static BSTree BSTreeDelete(BSTree t,ItemPQ element)
{
    if (t == NULL)                                  // if t is NULL
        return NULL;                                // end function
    else if (element.value < t->element.value)      
        t->left = BSTreeDelete(t->left, element);
    else if (element.value > t->element.value)      
        t->right = BSTreeDelete(t->right, element); // use recursion to find the position of the given element
    else // (v == t->value)
        t = deleteRoot(t);                          // if it is root 
    return t;                                       //creturn new BSTree
}

//given a key, find the node inside the tree.
static BSTNode findNode(BSTree t, int key) {
    if (t!= NULL){                      // t is not NULL
        if (t->element.key == key){     // if t is the node we want
            return t;                   // return t
        } else {                        // if not
            BSTNode foundNode = findNode(t->left, key); // use recursion to find the node that we what
            if (foundNode == NULL){                     
                foundNode = findNode(t->right, key);
            }
            return foundNode;                           // return foundNode if found
        }
    } else {
        return NULL; // return NULL if not found
    }
}
void updatePQ(PQ pq, ItemPQ element) {
    BSTNode node = findNode(pq->root, element.key);//traverse all nodes to find the key.
    //printf("THE NODE HAS BEEN FOUND key: %d, value:%d\n", node->element.key, node->element.value);
    //remove the node
    pq->root = BSTreeDelete(pq->root,node->element);
    //reinsert the new element into tree.
    pq->root = BSTreeInsert(pq->root, element);
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
            printf("left Side of key: %d\n", t->element.key);    // print the left side of the tree
            printBSTree(t->left);
        } 
        if (t->right!=NULL){
            printf("Right Side of key: %d\n", t->element.key);   // print the right side of the tree
            printBSTree(t->right);
        }
    }
}

void showPQ(PQ pq) {
    printBSTree(pq->root);   // show the tree
}

void freeTree(BSTree t){
    if (t == NULL) return;
    freeTree(t->left);       // free every node in the tree by using recursion
    freeTree(t->right);
    free(t);
}

void freePQ(PQ pq) {
    freeTree(pq->root);      // free every node in the tree
    free(pq);                // then free priority queue
}

