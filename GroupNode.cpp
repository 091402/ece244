//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below
#include "GroupNode.h"

GroupNode::GroupNode(string n) {
    name = n;
    myShapeList = new ShapeList;
    next = nullptr;
} // sets group name to n and makes myShapeList
// point to a new ShapeList; sets next to nullptr

GroupNode::~GroupNode() {
   // if (myShapeList != nullptr)
        delete myShapeList;

} // deletes the myShapeList list

string GroupNode::getName() const {
    return name;

} // returns group name

ShapeList* GroupNode::getShapeList() const {
    return myShapeList;
} // returns myShapeList

void GroupNode::setShapeList(ShapeList* ptr) {
    myShapeList = ptr;
} // sets myShapeList to ptr

GroupNode* GroupNode::getNext() const {
    return next;
} // returns next

void GroupNode::setNext(GroupNode* ptr) {
    next = ptr;
} // sets next to ptr

void GroupNode::print() const {
   cout<<name<<": "<<endl;
    if(myShapeList != nullptr){
    myShapeList->print();
    }
}


