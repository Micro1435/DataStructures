//
//  main.cpp
//  Assignment7
//
//  Created by Michael Montella on 3/2/16.
//  Copyright © 2016 Michael Montella. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"

using namespace std;

void printMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
}


int main(int argc, char * argv[]) {
    
    MovieTree movieTree;
    
    int choice = 0;
    
    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.good()) {
        //cout << "File opened bro" << endl;
        string data;
        while (getline(inFile, data)) {
            stringstream ss(data);
            
            // Movie Rank
            string rank;
            getline(ss, rank, ',');
            
            // Movie Title
            string title;
            getline(ss, title, ',');

            // Release Year
            string releaseYear;
            getline(ss, releaseYear, ',');
            
            // Quantity
            string quantity;
            getline(ss, quantity, ',');
            
            movieTree.addMovieNode(stoi(rank), title, stoi(releaseYear), stoi(quantity));
        }
    }
    
    while (choice != 6) {
        printMenu();
        cin >> choice;
        
        if (choice == 1) {
            // Find movie
            string title;
            cin.ignore();
            
            cout << "Enter title:" << endl;
            getline(cin, title);
            
            movieTree.findMovie(title);
        }
        
        if (choice == 2) {
            // Rent movie
            string title;
            cin.ignore();
            
            cout << "Enter title:" << endl;
            getline(cin, title);
            
            movieTree.rentMovie(title);
        }
        
        if (choice == 3) {
            // Print inventory
            movieTree.printMovieInventory();
        }
        
        if (choice == 4) {
            // Delete movie
            string title;
            cin.ignore();
            
            cout << "Enter title:" << endl;
            getline(cin, title);
            
            movieTree.deleteMovieNode(title);
        }
        
        if (choice == 5) {
            movieTree.countMovieNodes();
        }
        
        if (choice == 6) {
            cout << "Goodbye!" << endl;
        }
    }
    
    return 0;
}
