//
//  Assignment7.cpp
//  Assignment7
//
//  Created by Michael Montella on 3/2/16.
//  Copyright © 2016 Michael Montella. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {
    root = NULL;
}

MovieTree::~MovieTree() {
    //dtor
    DeleteAll(root);
}

// DELETE ALL MOVIES
void MovieTree::DeleteAll(MovieNode *node) {
    if (node != NULL) {
        DeleteAll(node->leftChild);
        DeleteAll(node->rightChild);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

// PRINT MOVIE INVENTORY
void MovieTree::printMovieInventory() {

    printMovieInventory(root);

}

void MovieTree::printMovieInventory(MovieNode *node) {

    if (node->leftChild != NULL) {
        printMovieInventory(node->leftChild);
    }

    cout << "Movie: " << node->title << " " << node->quantity << endl;
    if (node->rightChild != NULL) {
        printMovieInventory(node->rightChild);
    }
}

// ADD MOVIE NODE
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
    
    MovieNode *temp = new MovieNode;
    MovieNode *parent = NULL;
    
    temp->parent = NULL;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    
    
    MovieNode *node = new MovieNode(ranking, title, releaseYear, quantity);
    node->parent = NULL;
    node->rightChild = NULL;
    node->leftChild = NULL;
    
    temp = root;
    bool left = true;
    while (temp != NULL) {
        
        parent = temp;
        
        if (node->title.compare(temp->title) < 0) {
            // Go left

            temp = temp->leftChild;
            left = true;
            
        } else {
            // Go right

            temp = temp->rightChild;
            left = false;
        }
    }
    
    
    if (parent == NULL) {
        root = node;
    } else if (left) {
        // Left child
        parent->leftChild = node;
        node->parent = parent;
    } else {
        // Right child
        parent->rightChild = node;
        node->parent = parent;
    }
}

// FIND MOVIE
void MovieTree::findMovie(string title) {
    
    MovieNode *node = new MovieNode;
    node = root;
    bool exists = false;
    while (node != NULL) {
        
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            exists = true;
            break;
        }
    }
    
    if (exists) {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Year:" << node->year << endl;
        cout << "Quantity:" << node->quantity << endl;
    } else {
        cout << "Movie not found." << endl;
    }
}

// RENT MOVIE
void MovieTree::rentMovie(string title) {
    
    MovieNode *node = new MovieNode;
    node = root;
    bool exists = false;
    while (node != NULL) {
        
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            exists = true;
            break;
        }
    }
    
    if (exists) {
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Year:" << node->year << endl;
        cout << "Quantity:" << node->quantity - 1 << endl;
        
        node->quantity -= 1;
        
        if (node->quantity == 0) {
            deleteMovieNode(node->title);
        }
    } else {
        cout << "Movie not found." << endl;
    }
    
    

}

// COUNT MOVIE NODES
int MovieTree::countMovieNodes() {
    int totalMovies = 0;
    
    countMovieNodes(root, &totalMovies);
    
    cout << "Tree contains: " << totalMovies << " movies." << endl;
    return totalMovies;
}

void MovieTree::countMovieNodes(MovieNode *node, int *c) {
    if (node->leftChild != NULL) {
        countMovieNodes(node->leftChild, c);
    }
    *c = *c + 1;
    if (node->rightChild != NULL) {
        countMovieNodes(node->rightChild, c);
    }
}

// DELETE MOVIE NODE
void MovieTree::deleteMovieNode(string title) {
    MovieNode *node = new MovieNode;
    
    node = root;
    
    while (node != NULL) {
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            break;
        }
    }
    
    if (node->leftChild == NULL && node->rightChild == NULL) {
        // No Children
        

        if (node->title.compare(node->parent->title) < 0) {
            node->parent->leftChild = NULL;
        } else {
            node->parent->rightChild = NULL;
        }

        
    } else if (node->leftChild != NULL && node->rightChild != NULL) {
        // 2 Children
        
        MovieNode *temp = new MovieNode;
        
        temp = node->rightChild;

        if (temp->leftChild != NULL) {
            while (temp != NULL) {
                temp = temp->leftChild;
            }
        } else if (temp->rightChild != NULL) {
            temp = temp->rightChild;
        }
        
        if (node->parent->leftChild->title == node->title) {
            // Node is left child
            node->parent->leftChild = temp;
            temp->parent = node->parent;
            temp->leftChild = node->leftChild;
            if (temp->rightChild != NULL) {
                temp->rightChild->parent = temp;
            }
        } else {
            // Node is right child
            node->parent->rightChild = temp;
            temp->parent = node->parent;
            
        }
        

        
    } else {
        // 1 child
        
        if (node->leftChild == NULL) {                      // Node has right child
            node->rightChild->parent = node->parent;
            if (node->parent->rightChild == node) {             // Node is right child
                node->parent->rightChild = node->rightChild;
            } else {                                            // Node is left child
                node->parent->leftChild = node->rightChild;
            }

        } else if (node->rightChild == NULL) {
            node->leftChild->parent = node->parent;
            if (node->parent->rightChild == node) {             // Node is right child
                node->parent->rightChild = node->leftChild;
            } else {                                            // Node is left child
                node->parent->leftChild = node->leftChild;
            }
        }
        

    }
    
    delete node;
}

