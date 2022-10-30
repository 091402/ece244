//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int isKeyword(string command) {
    for (int i = 0; i < NUM_KEYWORDS; ++i) {
        if (command == keyWordsList[i])
            return i;
    }
    return -1;
}

int main() {
    // Create the groups list
    gList = new GroupList();

    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS - 1]);
    gList->insert(poolGroup);

    string line;
    string command;

    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        int kwFlag = isKeyword(command);
        switch (kwFlag) {
            case 0:
            {
                string n = " ", t = " ", last = " ";
                int xL = -1, yL = -1, xS = -1, yS = -1;
                bool flag = true;

                lineStream >> n;

                if (n == "shape" || n == "group" || n == "move" || n == "delete" || n == "draw" || n == "pool") {
                    cout << "error: invalid name" << endl;
                    flag = false;
                    break;
                }
                GroupNode* tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    if (tgnptr->getName() == n) {
                        cout << "error: name " << n << " exists" << endl;
                        flag = false;
                        break;
                    }
                    tgnptr = tgnptr->getNext();
                }
                  if (!flag)
                    break;
                tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    ShapeList* tslptr = tgnptr->getShapeList();
                    if (tslptr != nullptr) {
                        if (tslptr->find(n) != nullptr) {
                            cout << "error: name " << n << " exists" << endl;
                            flag = false;
                            break;
                        }
                    }
                    tgnptr = tgnptr->getNext();
                }
                if (!flag)
                    break;
                lineStream >> t;
                lineStream >>xL;
                lineStream >>yL;
                lineStream >>xS;
                lineStream >>yS;
                Shape* ptr = new Shape(n, t, xL, xS, yL, yS);
                ShapeNode* snptr = new ShapeNode;
                snptr->setShape(ptr);
                GroupNode* poolptr = gList->getHead();
                ShapeList* poolslptr = poolptr->getShapeList();
                poolslptr->insert(snptr);
                cout << n << ": " << t << " " << xL << " " << yL << " " << xS << " " << yS << endl;
                break;
            }
            case 1:
            {
                string gn;
                bool flag = true;
                lineStream >>gn;
                if (gn == "shape" || gn == "group" || gn == "move" || gn == "delete" || gn == "draw" || gn == "pool") {
                    cout << "error: invalid name" << endl;
                    flag = false;
                    break;
                }
                GroupNode* tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    if (tgnptr->getName() == gn) {
                        cout << "error: name " << gn << " exists" << endl;
                        flag = false;
                        break;
                    }
                    tgnptr = tgnptr->getNext();
                }
                if (!flag) break;
                tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    ShapeList* tslptr = tgnptr->getShapeList();
                    if (tslptr != nullptr) {
                        if (tslptr->find(gn) != nullptr) {
                            cout << "error: name " << gn << " exists" << endl;
                            flag = false;
                            break;
                        }
                    }
                    tgnptr = tgnptr->getNext();
                }
                if (!flag)
                    break;
                GroupNode* gnptr = new GroupNode(gn);
                gList->insert(gnptr);
                cout << gn << ": " << "group" << endl;
                break;

            }
            case 2:
            {
                string sn, gn;
                bool flag1 = false;
                bool flag2 = false;
                ShapeNode* snptr = nullptr;
                lineStream>>sn;
                if (sn == "shape" || sn == "group" || sn == "move" || sn == "delete" || sn == "draw" || sn == "pool") {
                    cout << "error: invalid name" << endl;
                    flag1 = false;
                    break;
                }
                lineStream>> gn;
                if (gn == "shape" || gn == "group" || gn == "move" || gn == "delete" || gn == "draw" || gn == "pool") {
                    cout << "error: invalid name" << endl;
                    flag2 = false;
                    break;
                }

                GroupNode* tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    ShapeList* tslptr = tgnptr->getShapeList();
                    if (tslptr != nullptr) {
                        snptr = tslptr->find(sn);
                        
                        //snptr = tslptr->remove(sn);
                        if (snptr != nullptr) {
                            flag1 = true;
                            break;
                        }
                    }
                    tgnptr = tgnptr->getNext();
                }
                if (!flag1) {
                    cout << "error: " << "shape " << sn << " not found" << endl;
                    break;
                }
                GroupNode* tgnptr1 = gList->getHead();
                while (tgnptr1 != nullptr) {
                    if (tgnptr1->getName() == gn) {
                        flag2 = true;
                        break;
                    }
                    tgnptr1 = tgnptr1->getNext();
                }
                if (!flag2) {
                    cout << "error: " << "group " << gn << " not found" << endl;
                    break;
                }
                tgnptr = gList->getHead();
                while (tgnptr != nullptr) {
                    ShapeList* tslptr = tgnptr->getShapeList();
                    if (tslptr != nullptr) {
                        snptr = tslptr->remove(sn); 
                        if(snptr != nullptr) break;
                    }
                    tgnptr = tgnptr->getNext();
                }
                
                tgnptr1->getShapeList()->insert(snptr);
                cout << "moved " << sn << " to " << gn << endl;
                break;
            }
            case 3:
            {
                string n;
                bool flag = false;
                lineStream>>n;
                if (n == "shape" || n == "group" || n == "move" || n == "delete" || n == "draw" || n == "pool") {
                    cout << "error: invalid name" << endl;
                    flag = false;
                    break;
                }
                GroupNode* tgnptr = gList->remove(n);
                if (tgnptr != nullptr) {
                    GroupNode* poolptr = gList->getHead();
                    ShapeList* poolslptr = poolptr->getShapeList();
                    ShapeList* slptr = tgnptr->getShapeList();
                    ShapeNode* snptr = slptr->getHead();

                    while (snptr != nullptr) {
                        ShapeNode* temp = snptr->getNext();
                        poolslptr->insert(snptr);   
                        snptr = temp;
                    }
                    slptr->setHead(nullptr);
                    delete slptr;
                    tgnptr->setShapeList(nullptr);
                    delete tgnptr;
                    flag = true;
                    cout << n << ": " << "deleted" << endl;
                }
                if(flag) break;
                tgnptr = gList->getHead();            
                while (tgnptr != nullptr) {
                    ShapeList* tslptr = tgnptr->getShapeList();
                    if (tslptr != nullptr) {
                       // ShapeNode* snptr = tslptr->find(n);
                        ShapeNode* snptr = tslptr->remove(n);
                        if (snptr != nullptr) {
                            delete snptr;
                            snptr = nullptr;
                            flag = true;
                            cout << n << ": " << "deleted" << endl;
                            break;
                        }
                    }
                    tgnptr = tgnptr->getNext();
                }
                if (!flag) {
                    cout << "error: " << "shape " << n << " not found" << endl;
                    break;
                }
                break;
            }
            case 4:
            {
                cout << "drawing: " << endl;
                gList->print();
                break;
            }

        }
        command = "";
        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);

    } // End input loop until EOF.
   // delete gList;
    return 0;

}

