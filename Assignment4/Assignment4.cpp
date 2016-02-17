// Michael Montella
// Assignment 4

#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

void displayMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}

int main(){
  CommunicationNetwork linkedStuff;
  string cityName;
  string prevCityName;

  int userChoice = 0;
  
  while(userChoice != 7){
    displayMenu();
    cin >> userChoice;

    if(userChoice == 1){
      linkedStuff.buildNetwork();
    }
    else if(userChoice == 2){
      linkedStuff.printNetwork();
    }
    else if(userChoice == 3){
      linkedStuff.transmitMsg("messageIn.txt");
    }
    else if(userChoice == 4){
      /*cout << "Enter a city name:" << endl;
      cin >> cityName;
      cout << "Enter a previous city name:" << endl;
      cin >> prevCityName;*/
      cin.ignore();
      cout << "Enter a city name: " << endl;
      //cin >> cityName;
      getline(cin,cityName);
      cout << "Enter a previous city name: " << endl;
      //cin >> prevCityName;
      getline(cin,prevCityName);

      linkedStuff.addCity(prevCityName, cityName);
    }
    else if(userChoice == 5){
        //Delete Network
        cin.ignore();
        string cityNameDelete;
        cout << "Enter a city name: " << endl;
        getline(cin, cityNameDelete);
        linkedStuff.deleteCity(cityNameDelete);
    }
    else if(userChoice == 6) {
        //Clear Network
        linkedStuff.clearNetwork();
    } else if (userChoice == 7) {
        cout << "Goodbye!" << endl;
    }

  }
  return 0;
}
