//
//  BST.cpp
//  Binary Search Tree
//
//  Created by Guancheng Lai on 12/6/17.
//  Copyright © 2017 Guancheng Lai. All rights reserved.
//


#include "BST.h"
#include <iostream>
#include <string>

//This function return true if the current pointer is pointing
//to a non-child node. Or return false if it is not.
bool leaf(Node * ptr) {
    if (ptr->lt == NULL && ptr->rt == NULL)
        return true;
    else
        return false;
}

//This function return true if the current pointer is pointing
//to a two child node. Or return false if it is not.
bool twoChild(Node * ptr) {
    if (ptr->lt != NULL && ptr->rt != NULL)
        return true;
    else
        return false;
}

//This function return true if the current pointer is pointing
//to a one child node. Or return false if it is not.
bool oneChild(Node * ptr) {
    if (ptr->lt != NULL && ptr->rt == NULL)
        return true;
    else if (ptr->lt == NULL && ptr->rt != NULL)
        return true;
    else
        return false;
}

//Constructor of the Binary search tree
BST::BST()
{
    Root = NULL;
}

//Destructor of the Binary search tree
BST::~BST()
{
    DeleteTree(Root);
}

//This function is to handle the insertion into the binary search tree
bool BST::Insert(std::string info)
{
    //Allocate memory for the new information
    Node * p = new Node;
    p->word = info;
    p->lt = NULL;
    p->rt = NULL;
    
    //Insert into a Root case
    if (Root == NULL) {
        Root = p;
        p->word = info;
        p->lt = NULL;
        p->rt = NULL;
        return true;
    }
    
    //Insert into a Leaf case
    bool inserted = false;
    Node * cur = Root;
    Node * parent = cur;
    
    while (inserted == false) {
        
        //Go left if info is lower than current node
        if (info <= cur->word)
        {
            if (cur->lt == NULL)
            {
                cur->lt = p;
                cur->lt->word = info;
                inserted = true;
                return true;
                //Inserted if the current node doesnot have a left tree
            }
            else
            {
                //Current pointer continue go left
                cur = cur->lt;
            }
        }
        
        //Go right if info is higner than the current node
        else
        {
            if (cur->rt == NULL)
            {
                cur->rt = p;
                cur->rt->word = info;
                inserted = true;
                return true;
                //Inserted if the current node doesnot have a right tree
            }
            else
            {
                //Current pointer continue go right
                cur = cur->rt;
            }
        }
    }
    return  false;
}

//This function is to handle the delete of the
//binary search tree.
bool BST::Delete(std::string info)
{
    if (Root == NULL)
        return false;
    
    Node * cur = Root;
    bool searched = false;
    Node * parent = cur;    //Parent pointer of current node
    
    //Searching for the target to delete
    while (searched == false)
    {
        if (info == cur->word)
        {
            searched = true;
        }
        else if (info < cur->word)
        {
            if (cur->lt == NULL)
                return false;
            else
            {
                parent = cur;
                cur = cur->lt;
            }
        }
        else
        {
            if (cur->rt == NULL)
                return false;
            else
            {
                parent = cur;
                cur = cur->rt;
            }
        }
    }
    
    
    //Leaf case
    if (leaf(cur))
    {
        //delete a root as a leaf case
        if (cur == Root)
        {
            Root = NULL;
        }
        
        //set the left or right pointer to nullptr
        if (parent->lt == cur)
        {
            parent->lt = NULL;
        }
        else if (parent->rt == cur)
        {
            parent->rt = NULL;
        }
        
        delete cur;
        cur = NULL;
        return true;
    }
    
    //delete a two child node
    else if (twoChild(cur))
    {
        Node * temp = cur;
        
        
        //Algorithm that looking for a median in a BST
        //Go one left and far right until the "rt" pointing to a nullptr.
        parent = cur;
        cur = cur->lt;
        while (cur->rt != NULL)
        {
            parent = cur;
            cur = cur->rt;
        }
        
        //Assign the median node value to the deleted node
        temp->word = cur->word;
        
        
        if (parent == temp)
        {
            //Situation that the median value is the left child of the target delete node
            parent->lt = cur->lt;
        }
        else if (parent->rt->lt != NULL)
        {
            //Situation that the median value node has a child on the left side
            parent->rt = cur->lt;
        }
        else
        {
            //set the parent node right pointer to nullptr
            parent->rt = NULL;
        }
        
        delete cur;
        cur = NULL;
        return true;
    }
    
    //One child case
    else if (oneChild (cur)) {
        if (cur == Root && cur->lt == NULL)     //Root as a one child node
        {
            Root = cur->rt;
            delete cur;
            cur = NULL;
            parent = NULL;
        }
        else if (cur == Root && cur->rt == NULL)//Root as a one child node
        {
            Root = cur->lt;
            delete cur;
            cur = NULL;
            parent = NULL;
        }
        else if (cur->lt == NULL && cur->word < parent->word)
        {
            parent->lt = cur->rt;
            delete cur;
            cur = NULL;
        }
        else if(cur->lt == NULL && cur->word > parent->word)
        {
            parent->rt = cur->rt;
            delete cur;
            cur = NULL;
        }
        else if (cur->rt == NULL && cur->word < parent->word)
        {
            parent->lt = cur->lt;
            delete cur;
            cur = NULL;
        }
        else if (cur->rt == NULL && cur->word > parent->word)
        {
            parent->rt = cur->lt;
            delete cur;
            cur = NULL;
        }
        return true;
    }
    return false;
}

//Print function is to print out the binary search tree
void BST::Print()
{
    Inorder(Root);
}

//Helping function for the print function
void BST::Inorder(Node * ptr)
{
    if (Root != NULL)
    {
        //Inorder traversal
        if (ptr->lt != NULL)
        {
            Inorder(ptr->lt);
        }
        cout << ptr->word << endl;   //output the value
        if (ptr->rt != NULL)
        {
            Inorder(ptr->rt);
        }
    }
    else
    {
        cout << "The tree is empty\n";
    }
}

//Helping function for the destructor
void BST::DeleteTree(Node * ptr)
{
    if (Root != NULL)
    {
        //post-order traversal
        if (ptr->lt != NULL)
        {
            DeleteTree(ptr->lt);
        }
        if (ptr->rt != NULL)
        {
            DeleteTree(ptr->rt);
        }
        delete ptr;
        ptr = NULL;
    }
}

