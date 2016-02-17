// Michael Montella
// Assignment 4

#include "CommunicationNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CommunicationNetwork::CommunicationNetwork(){
  
}

CommunicationNetwork::~CommunicationNetwork(){
  //dtor
    
    City *current = CommunicationNetwork::head;
    City *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        cout << "deleting " << temp->cityName << endl;
        delete temp;
    }
    head = NULL;
}

void CommunicationNetwork::addCity(string previousCity, string newCity){
    // Insert new city after the previousCity, new city is newCity
    City *cityNew = new City;
    cityNew->cityName = newCity;
    cityNew->next = NULL;
    City *current = CommunicationNetwork::head;
    while(current!=NULL){
        if (previousCity == "First") {
            cityNew->next = current;
            cityNew->previous = NULL;
            current->previous = cityNew;
            head = cityNew;
            break;
        }else if(current->cityName==previousCity){
            cityNew->next = current->next;
            current->next = cityNew;
            cityNew->previous = current;
            break;
        }
        current = current->next;
    }
}

void CommunicationNetwork::transmitMsg(char *filename){
    // Open the file and transmit messages between all cities. Only one city
    // can hold the message at a time.
    ifstream inFile;
    inFile.open(filename);
    string data;
    City *current = CommunicationNetwork::head;
    if(current->cityName!="Los Angeles"){
        cout << "Empty list" << endl;
    }else{
        if(inFile.good()){
            while(getline(inFile,data)){
                stringstream ss(data);
                string word;
                while(ss>>word){
                    current = CommunicationNetwork::head;
                    while(current != NULL){
                        
                        if (current->next != NULL) {
                            current->message=word;
                            cout << current->cityName << " received " << current->message << endl;
                            current->message="";
                        } else if (current->next == NULL) {
                            current->message = word;
                            cout << current->cityName << " received " << current->message << endl;
                            break;
                        }
                        current = current->next;
                    }
                    
                    while (current != NULL) {
                        current = current ->previous;
                        if (current->previous != NULL) {
                            current->message = word;
                            cout << current->cityName << " received " << current->message << endl;
                            current->message = "";
                        } else if (current->previous == NULL) {
                            current->message = word;
                            cout << current->cityName << " received " << current->message << endl;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void CommunicationNetwork::printNetwork(){
    City *current = CommunicationNetwork::head;
    cout << "===CURRENT PATH===" << endl;
    while(current != NULL){
        if (current->previous == NULL) {
            cout << "NULL <- ";
            cout << current->cityName << " <-> ";
        } else if (current->next != NULL) {
            cout << current->cityName << " <-> ";
        } else {
            cout << current->cityName << " -> ";
            ;
        }
        current = current->next;
    }
    cout << "NULL" << endl;
    cout << "==================" << endl;

}

void CommunicationNetwork::buildNetwork(){
    string startCities[]={"Los Angeles", "Phoenix", "Denver",
		      "Dallas", "St. Louis", "Chicago",
		      "Atlanta", "Washington, D.C.", "New York",
		      "Boston"};
    CommunicationNetwork::head=new City; //makes new City pointer array
    CommunicationNetwork::head->cityName = startCities[0]; //assigns cityname to LA
    CommunicationNetwork::head->next = NULL; //assigns the next(pointer) to NULL
    CommunicationNetwork::head->previous = NULL; // Assigns previous pointer to NULL

    City *current = CommunicationNetwork::head; //new City pointer point to head

    int i=1;
    //
    while(i<10){
        City *temp = new City;
        temp->cityName = startCities[i]; //temp value to a city
        temp->next = NULL; //temp next value is zero
        temp->previous = current; // Temp previous value is current
        current->next = temp; //current/head next value has pointer value of temp
        current = current->next; //current now points to temp
        i++;
    }
    CommunicationNetwork::tail = current;
    current = CommunicationNetwork::head;
    cout << "===CURRENT PATH===" << endl;
    while(current != NULL){
        if (current->previous == NULL) {
            cout << "NULL <- ";
            cout << current->cityName << " <-> ";
        } else if (current->next != NULL) {
            cout << current->cityName << " <-> ";
        } else {
            cout << current->cityName << " -> NULL" << endl;
        }
        current = current->next;
    }
    cout << "==================" << endl;
}

void CommunicationNetwork::deleteCity(string cityNameDelete){
    City *temp = CommunicationNetwork::head;            //Set temp to head of network
    City *current = new City;
    while (temp != NULL) {                              //Loop through network until city is found
        if (head->cityName == cityNameDelete) {
            temp = head;
            head = head->next;
            head->previous = NULL;
            
            delete temp;
            break;
        } else if (temp->next == NULL && temp->cityName == cityNameDelete){
            current = temp->previous;
            current->next = NULL;
            tail = current;
            
            delete temp;
            break;
        } else if (temp->cityName == cityNameDelete) {
            current = temp->next;
            current->previous = temp->previous;
            current = temp->previous;
            current->next = temp->next;
            
            delete temp;
            break;
        }
        temp = temp->next;
    }
}

void CommunicationNetwork::clearNetwork() {
    City *current = CommunicationNetwork::head;
    City *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        cout << "deleting " << temp->cityName << endl;
        delete temp;
    }
    head = NULL;
}
