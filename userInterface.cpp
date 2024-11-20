//
// Created by Xital on 11/15/2024.
//

#include "userInterface.h"

userInterface::userInterface() {
    //clear existing index handler and recreate it
    iH = nullptr;
    clearIndex();
}

userInterface::userInterface(const userInterface & userI) {
    //dereferencing
    iH = new indexHandler(*userI.iH);
    dp = userI.dp;
    qe = userI.qe;
}

userInterface & userInterface::operator=(const userInterface & userI) {
    delete iH;
    iH = new indexHandler(*userI.iH);
    dp = userI.dp;
    qe = userI.qe;
    return *this;
}

userInterface::~userInterface() {
    delete iH;
}

void userInterface::startUserInterface() {
    while(true) {
        cout << "Choose one of the options: " << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Run Document Parser" << endl;
        cout << "2 - Create Persistence" << endl; //prompt user
        cout << "3 - Read Persistence" << endl;
        cout << "4 - Run Query" << endl;    //prompt user

        //variable for users input
        string choice;
        getline(cin, choice);

        //preforming option user chose
        if(choice == "0") {
            break;
        }
        else if(choice == "1") {
            string path;
            //asking user for path archive
            cout << '\n' << "Enter path here: " << endl;
            getline(cin, path);
            runDocParser(path);
        }
        else if(choice == "2") {
            //calling create persistence function
            createPersistence();
        }
        else if(choice == "3") {
            //calling the read persistence function
            readPersistence();
        }
        else if(choice == "4") {
            //prompting user for query
            string query;
            cout << '\n' << "Enter query here: " << endl;
            getline(cin, query);
            runQueryEngine(query);
        }
        else {
            cout << "Invalid choice, please enter a valid input: " << endl;
        }

    }
}

void userInterface::runDocParser(string pathArc) {
    try {
        //clearing previous results from running the document parser
        clearIndex();
        dp.readFolder(pathArc);
    }
    catch(const exception &err){
        cerr << "Error: Could not run Document Parser! " << endl;
        //gives error message
        cerr << err.what() << endl;
    }
}


void userInterface::createPersistence() {
        try {
            iH->makePersist();
        }
        catch(const exception &err){
            cerr << "Error: Could not run creating persistence! " << endl;
            //gives error message
            cerr << err.what() << endl;
        }
}

void userInterface::readPersistence(){
    try {
        //clearing previous results from reading persistence
        clearIndex();
        iH->readPersist();
    }
    catch(const exception &err){
        cerr << "Error: Could not run reading persistence! " << endl;
        //gives error message
        cerr << err.what() << endl;
    }

}

void userInterface::runQueryEngine(string query) {
    try {
        vector<pair<double, string>> results = qe.parseQuery(query);
        if(results.size() > 0) {
            //keep looping until end of vector or until 15 searches
            for(int i = 0; i < 15 && i < results.size(); i++) {
                //returning string in the pair
                DocInfo doc = dp.getDocData(results[i].second);
                cout << "Result: " << i+1 << endl;
                cout << "Title: " << doc.title << endl;
                cout << "Publication: " << doc.publication << endl;
                cout << "Date: " << doc.date << endl;
                cout << endl;
            }
            string choice;
            while(choice != "0") {
                cout << '\n' << "Enter result number to view text or 0 to quit..." << endl;
                getline(cin, choice);
                //turning getline into an int and subtracting from the index we added to previously
                int index = stoi(choice) - 1;
                //checking to see if index is a valid input and if it is them it prints the text
                if(index >= 0 && index < 15 && index < results.size()) {
                    DocInfo doc = dp.getDocData(results[index].second);
                    cout << doc.text << endl;
                }
            }
        }
        else {
            cout << "No results were found" << endl;
        }
    }
    catch(const exception &err){
        cerr << "Error: Could not run Query! " << endl;
        //gives error message
        cerr << err.what() << endl;
    }
}

void userInterface::clearIndex() {
    //deletes any previous index handler
    delete iH;
    // creates a new index handler object
    iH = new indexHandler();
    //setting the information about the doc parser and query engine to the new index handler
    dp.setIndex(iH);
    qe.setIndexHandler(iH);

}
