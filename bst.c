#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "bst.h"

// Local functions

// These are stubs.  That is, you need to implement these functions.

BST * NewBST()
{
    BST * tree = malloc(sizeof(BST)); //allocates space for BST
    tree->left = NULL; //sets left side of tree to null
    tree->right = NULL; //sets right side of tree to null
    return tree; //returns new tree
}

void TreeInsert(BST * pBST, void * satellite, long long key)
{
    if(pBST->sat == NULL) //if the root node is empty...
    {
        pBST->sat = satellite; //sets root node data to satellite
        pBST->key = key; //sets root node key to key
        pBST->left = NULL; //makes sure that the left child is null
        pBST->right = NULL; //makes sure that the right child is null
    }
    else if(pBST->key > key) //if the key should be to the left of the root...
    {
        if(pBST->left==NULL) //if there is no left node...
        {
            pBST->left = NewBST(); //create one
        }
        TreeInsert(pBST->left,satellite,key); //inserts the satellite to the left
    }
    else //if the key should be to the right of the root...
    {
        if(pBST->right==NULL) //if there is no right node...
        {
            pBST->right = NewBST(); //create one
        }
        TreeInsert(pBST->right,satellite,key); //inserts satellite to the right
    }
}

void InOrder(BST * p, NODEVISITFUNC func)
{
    if(p!=NULL) //if the node exists...
    {
        InOrder(p->left,func); //print the nodes to its left
        func(p->sat); //print itself
        InOrder(p->right,func); //print the nodes to its right
    }
}

void PreOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST!=NULL) //if the node exists...
    {
        func(pBST->sat); //print itself
        InOrder(pBST->left,func); //print the nodes to its left
        InOrder(pBST->right,func); //print the nodes to its right
    }
}


void PostOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST!=NULL) //if the node exists...
    {
        InOrder(pBST->left,func); //print the nodes to its left
        InOrder(pBST->right,func); //print the nodes to its right
        func(pBST->sat); //print itself
    }
}


void * Search(BST * pBST, long long key)
{
    if(pBST->key == key) //if the root node has the correct key
    {
        return (pBST->sat); //return the satellite from the root
    }
    else if(pBST->key < key) //if the correct key is to the right of the root...
    {
        if(pBST->right==NULL) //if there IS no right root...
        {
            return NULL; //return null
        }
        else //if there IS a right root...
        {
            return Search(pBST->right,key); //search there instead
        }
    }
    else //if the correct key is to the left of the root...
    {
        if(pBST->left==NULL) //if there IS no left root...
        {
            return NULL; //return null
        }
        else //if there IS a left root...
        {
            return Search(pBST->left,key); //search there instead
        }
    }
}


void TreeDelete(BST * pBST, long long key)
{
    //find correct node:
    BST* parent;
    while((pBST->key)!=key) //while pBST doesn't point to the correct node...
    {
        if(pBST->key < key) //if the correct key is to the right of the root...
        {
            if(pBST->right==NULL) //if there IS no right root...
            {
                return; //the node is already deleted
            }
            else //if there IS a right root...
            {
                parent = pBST;
                pBST=pBST->right; //search there instead
            }
        }
        else if(pBST->key > key)//if the correct key is to the left of the root...
        {
            if(pBST->left==NULL) //if there IS no left root...
            {
                return; //the node is already deleted
            }
            else //if there IS a left root...
            {
                parent = pBST;
            pBST=pBST->left; //search there instead
            }
        }
    }

    //delete node:
    if(pBST->right==NULL && pBST->left == NULL) //if the node has no children...
    {
        if(parent->left==pBST) //if the node is a left node...
        {
            parent->left = NULL;//sets parent's left node to null
        }
        else //if the node is a right node...
        {
            parent->right = NULL;//sets parent's right node to null
        }
        pBST = NULL; //sets node to NULL
        free(pBST); //frees node

    }
    else if(pBST->right==NULL && pBST->left!=NULL) //if the node only has a left child...
    {
        if(parent->left==pBST) //if the node is a left node...
        {
            parent->left = pBST->left;//sets parent's left node to the current node's left node
        }
        else //if the node is a right node...
        {
            parent->right = pBST->left;//sets parent's right node to the current node's left node
        }
        pBST = NULL; //sets node to NULL
        free(pBST); //frees node
    }
    else if (pBST->left==NULL && pBST->right!=NULL) //if the node only has a right child...
    {
        if(parent->left==pBST) //if the node is a left node...
        {
            parent->left = pBST->right;//sets parent's left node to the current node's right node
        }
        else //if the node is a right node...
        {
            parent->right = pBST->right;//sets parent's right node to the current node's right node
        }
        pBST = NULL; //sets node to NULL
        free(pBST); //frees node
    }
    else //if the node has TWO child nodes...
    {
        BST* temp = pBST->right; //sets temp to the right node of the current node
        while(temp->left!=NULL)
        {
            parent = temp;
            temp = temp->left; //finds the leftmost right node
        }
        pBST->sat = temp->sat; //sets the node's value to the temp node
        pBST->key = temp->key; //sets the node's value to the temp node
        parent->left = temp->right;//sets parent's left node to the temp node's right node, just in case there were more nodes further to the right
        temp = NULL; //sets temp node to NULL
        free(temp); //frees temp node, now that it's data has overridden the original node
    }
}

