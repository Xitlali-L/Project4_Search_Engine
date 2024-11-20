#include <iostream>
#include "userInterface.h"
#include "DocParser.h"


int main(int argc, char** argv){
    // for (int i = 1; i < argc; i++) {
    //     std::cout << argv[i] << std::endl;
    // }
    //if it is less than 2 command lines
   if(argc < 2) {
       cout << "ERROR: NOT enough command line arguments" << endl;
       exit(1);
   }

    //if first command line v is "index"
    else {
        string mode = argv[1];
        userInterface useri;
        if(mode == "index") {
            //make sure we have the correct command line
            if(argc < 3) {
                cout << "ERROR: NOT enough command line arguments" << endl;
                exit(1);
            }
            //passing in the directory where the json files are
            useri.runDocParser(argv [2]);
            useri.createPersistence();
        }
        else if(mode == "query") {
            //making sure we have enough arguments
            if(argc < 3) {
                cout << "ERROR: NOT enough command line arguments" << endl;
                exit(1);
            }
            useri.readPersistence();
            useri.runQueryEngine(argv [2]);
        }
        else if(mode == "ui") {
            useri.startUserInterface();
        }
        else {
            cout << "ERROR: invalid run mode!" << endl;
            exit(1);
        }
    }
    return 0;
}
