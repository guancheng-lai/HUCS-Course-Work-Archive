//
//  BST.h
//  Binary Search Tree
//
//  Created by Guancheng Lai on 12/6/17.
//  Copyright © 2017 Guancheng Lai. All rights reserved.
//

#ifndef BST_h
#define BST_h


#endif /* BST_h */
#pragma once
/********************************************************************
 File: BST.h
 Des:  This file contains the class definition for a Binary Search
 Tree (A)bstract (D)ata (T)ype.
 
 
 Author: Coach Rags
 ********************************************************************/
#include <string>
using namespace std;

struct Node
{
    string word;
    Node* lt;
    Node* rt;
};

//Class definition for a Binary Search Tree
class BST
{
public:
    
    //constructor
    BST();
    
    //destructor
    ~BST();
    
    //add a node to the BST
    bool Insert(string);
    
    //delete a node from the BST
    bool Delete(string);
    
    //print out the entire list
    void Print();
    
private:
    //release all node storage back to OS
    void DeleteTree(Node*);
    
    //recursive function to print out BST data in alphabetical order
    void Inorder(Node*);
    
    Node* Root;
};
