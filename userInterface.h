//
// Created by Xital on 11/15/2024.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "queryEngine.h"
#include "DocParser.h"

class userInterface {
private:
    indexHandler* iH;
    DocParser dp;
    queryEngine qe;

public:
    userInterface();
    //RULE OF THREE
    //copy constructor (initializing copy of a new object)
    userInterface(const userInterface&);
    //assignment operator (overwriting an existing value)
    userInterface& operator=(const userInterface&);
    //destructor (deleting memory)
    ~userInterface();

    void startUserInterface();

    //function for each option
    void runDocParser(string);
    void createPersistence();
    void readPersistence();
    void runQueryEngine(string);
    void clearIndex();
};



#endif //USERINTERFACE_H
