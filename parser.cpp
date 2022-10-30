//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

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
            case -1:
                cout << "Error: invalid command" << endl;
                break;
            case 1:
                lineStream >> max_shapes;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                    }
                } else {
                    if (shapesArray != NULL) {
                        for (int j = 0; j < max_shapes; ++j) {
                            delete shapesArray[j];
                        }
                        delete []shapesArray;
                        shapesArray = NULL;
                        shapeCount = 0;
                    }
                    shapesArray = new Shape*[max_shapes];
                    for (int i = 0; i < max_shapes; ++i) {
                        shapesArray[i] = NULL;
                    }
                    cout << "New database: max shapes is " << max_shapes << endl;
                }
                break;
            case 2:
            {
                string n = " ", t = " ", last = " ";
                int xL = -1, yL = -1, xS = -1, yS = -1;
                bool flag = false;

                lineStream >> n;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (n == "all" || n == "maxShapes" || n == "create" || n == "move" || n == "rotate" || n == "draw" || n == "delete" || n == "circle" || n == "ellipse" || n == "rectangle" || n == "triangle") {
                    cout << "Error: invalid shape name" << endl;
                    break;
                }
                if (shapesArray != NULL);
                for (int i = 0; i < shapeCount; ++i) {
                    if (shapesArray[i] != NULL && n == shapesArray[i] ->getName()) {
                        flag = true;
                    }
                }
                if (flag) {
                    cout << "Error: shape " << n << " exists" << endl;
                    break;
                }

                lineStream >> t;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (t != "circle" && t != "ellipse" && t != "rectangle" && t != "triangle") {
                    cout << "Error: invalid shape type" << endl;
                    break;
                }

                lineStream >>xL;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                char next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }

                if (xL < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>yL;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (yL < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>xS;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (xS < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>yS;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (yS < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }
                if (t == "circle" && xS != yS) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>last;
                if (last != " ") {
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                if (shapeCount >= max_shapes) {
                    cout << "Error: shape array is full" << endl;
                    break;
                }
                Shape* ptr = new Shape(n, t, xL, xS, yL, yS);
                shapesArray[shapeCount] = ptr;
                shapeCount++;
                cout << "Created" << " " << n << ": " << t << " " << xL << " " << yL << " " << xS << " " << yS << endl;
                break;
            }
            case 3:
            {
                int x, y;
                string n_one, last = " ";
                bool flag = false;

                lineStream >> n_one;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (n_one == "all" || n_one == "maxShapes" || n_one == "create" || n_one == "move" || n_one == "rotate" || n_one == "draw" || n_one == "delete" || n_one == "circle" || n_one == "ellipse" || n_one == "rectangle" || n_one == "triangle") {
                    cout << "Error: invalid shape name" << endl;
                    break;
                }
                if (shapesArray == NULL) break;
                for (int i = 0; i < shapeCount; ++i) {
                    if (shapesArray[i] != NULL && n_one == shapesArray[i]->getName()) {
                        flag = true;
                    }
                }
                if (!flag) {
                    cout << "Error: shape " << n_one << " not found" << endl;
                    break;
                }

                lineStream>>x;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                char next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (x < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream>>y;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (y < 0) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>last;
                if (last != " ") {
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                for (int i = 0; i < shapeCount; ++i) {
                    if (shapesArray[i] != NULL && n_one == shapesArray[i] ->getName()) {
                        shapesArray[i]->setXlocation(x);
                        shapesArray[i]->setYlocation(y);
                    }
                }
                cout << "Moved " << n_one << " to " << x << " " << y << endl;
                break;
            }
            case 4:
            {
                int a;
                string two, last = " ";
                int moveCount = 0;
                bool flag = false;

                lineStream >> two;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (two == "all" || two == "maxShapes" || two == "create" || two == "move" || two == "rotate" || two == "draw" || two == "delete" || two == "circle" || two == "ellipse" || two == "rectangle" || two == "triangle") {
                    cout << "Error: invalid shape name" << endl;
                    break;
                }
                if (shapesArray == NULL) break;
                for (int i = 0; i < shapeCount; ++i) {
                    if (shapesArray[i] != NULL && two == shapesArray[i]->getName()) {
                        flag = true;
                    }
                }
                if (!flag) {
                    cout << "Error: shape " << two << " not found" << endl;
                    break;
                }

                lineStream>>a;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                char next = lineStream.peek();
                if (next != ' ' && !lineStream.eof()) {
                    cout << "Error: invalid argument" << endl;
                    break;
                }
                if (a < 0 || a > 360) {
                    cout << "Error: invalid value" << endl;
                    break;
                }

                lineStream >>last;
                if (last != " ") {
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                cout << "Rotated " << two << " by " << a << " " << "degrees" << endl;
                break;
            }
            case 5:
            {
                string two, last = " ";
                bool flag = false;

                lineStream >> two;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (two == "maxShapes" || two == "create" || two == "move" || two == "rotate" || two == "draw" || two == "delete" || two == "circle" || two == "ellipse" || two == "rectangle" || two == "triangle") {
                    cout << "Error: invalid shape name" << endl;
                    break;
                }
                if (shapesArray != NULL)
                    for (int i = 0; i < shapeCount; ++i) {
                        if (shapesArray[i] != NULL && two == shapesArray[i]->getName()) {
                            flag = true;
                        }
                    }
                if (!flag && two != "all") {
                    cout << "Error: shape " << two << " not found" << endl;
                    break;
                }

                lineStream >>last;
                if (last != " ") {
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                if (two != "all") {
                    if (shapesArray == NULL) break;
                    for (int i = 0; i < shapeCount; ++i) {
                        if (shapesArray[i] != NULL && two == shapesArray[i]->getName())
                            cout << "Drew" << shapesArray[i]->getName() << ": " << shapesArray[i]->getType() << " " << shapesArray[i]->getXlocation() << " " << shapesArray[i]->getYlocation()
                            << " " << shapesArray[i]->getXsize() << " " << shapesArray[i]->getYsize() << endl;
                    }
                    break;
                }
                if (two == "all") {
                    cout << "Drew all shapes" << endl;
                    if (shapesArray == NULL) break;
                    for (int i = 0; i < shapeCount; ++i) {
                        if (shapesArray[i] != NULL)
                            cout << shapesArray[i]->getName() << ": " << shapesArray[i]->getType() << " " << shapesArray[i]->getXlocation() << " " << shapesArray[i]->getYlocation()
                            << " " << shapesArray[i]->getXsize() << " " << shapesArray[i]->getYsize() << endl;
                    }
                    break;
                }
            }
                break;
            case 6:
            {
                string two, last = " ";
                bool flag = false;
                lineStream >> two;
                if (lineStream.fail()) {
                    if (lineStream.eof()) {
                        cout << "Error: too few arguments" << endl;
                        break;
                    } else {
                        cout << "Error: invalid argument" << endl;
                        break;
                    }
                }
                if (two == "maxShapes" || two == "create" || two == "move" || two == "rotate" || two == "draw" || two == "delete" || two == "circle" || two == "ellipse" || two == "rectangle" || two == "triangle") {
                    cout << "Error: invalid shape name" << endl;
                    break;
                }
                if (shapesArray == NULL) break;
                for (int i = 0; i < shapeCount; ++i) {
                    if (shapesArray[i] != NULL && two == shapesArray[i]->getName()) {
                        flag = true;
                    }
                }
                if (!flag && two != "all") {
                    cout << "Error: shape " << two << " not found" << endl;
                    break;
                }

                lineStream >>last;
                if (last != " ") {
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                if (two != "all") {
                    for (int i = 0; i < shapeCount; ++i) {
                        if (shapesArray[i] != NULL && two == shapesArray[i]->getName()) {
                            delete shapesArray[i];
                            shapesArray[i] = NULL;
                            cout << "Deleted shape " << two << endl;
                        }
                    }
                    break;
                }
                if (two == "all") {
                    for (int i = 0; i < shapeCount; ++i) {
                        delete shapesArray[i];
                    }
                    delete []shapesArray;
                    shapesArray = NULL;
                    cout << "Deleted: all shapes" << endl;
                    break;
                }
            }
                break;
        }


        command = "";
        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);

    } // End input loop until EOF.

    return 0;
}

