//
// Created by Xitlali on 11/12/2024.
//

#include "indexHandler.h"

void indexHandler::makePersist() {
    ofstream outFile ("persist.txt");
    //number of words
    outFile << words.getSize() << endl;
    //go through the tree and print them
    words.printTree(outFile);

    //number of people
    outFile << ppl.getSize() << endl;
    //go through the tree and print them
    ppl.printTree(outFile);

    //number of organizations
    outFile << orgs.getSize() << endl;
    //go through the tree and print them
    orgs.printTree(outFile);

    //close file
    outFile.close();
}

//read files and populate the trees
void indexHandler::readPersist() {
    ifstream inFile ("persist.txt");
    if (!inFile.is_open()) {
        cout << "ERROR : File failed to open" <<endl;
        //closes entire program
        exit(1);
    }
    //resets the trees
    words.clear();
    ppl.clear();
    orgs.clear();

    //creating a buffer
    string buffer;
    //read first line for our number
    getline(inFile, buffer);

    //stoi converting buffer into int
    int count = stoi(buffer);

    //adding the nodes into the tree
    for (int i = 0; i < count; i++) {
        getline(inFile, buffer);
        //getline from a string as if it was a input file
        stringstream ss(buffer);

        //reading in the key
        string word;
        getline(ss, word, ';');

        //while file hasn't ended
        while(!ss.eof()) {
            string doc, freqStr;

            //reading the document until ',' and the am with frequency with ';'
            getline(ss, doc, ',');
            getline(ss, freqStr, ';');

            //counting the frequency
            int freq = stoi(freqStr);

            //inserting the word into tree word, document found in, and frequency
            words.insert(word, doc, freq);
        }
    }


    //for people
    getline(inFile, buffer);

    //stoi converting buffer into int
    count = stoi(buffer);

    //adding the nodes into the tree
    for (int i = 0; i < count; i++) {
        getline(inFile, buffer);
        //getline from a string as if it was a input file
        stringstream ss(buffer);

        //reading in the key
        string person;
        getline(ss, person, ';');

        //while file hasn't ended
        while(!ss.eof()) {
            string doc, freqStr;

            //reading the document until ',' and the am with frequency with ';'
            getline(ss, doc, ',');
            getline(ss, freqStr, ';');

            //counting the frequency
            int freq = stoi(freqStr);

            //inserting the word into tree word, document found in, and frequency
            ppl.insert(person, doc, freq);
        }

    }


    //for organizations
    getline(inFile, buffer);

    //stoi converting buffer into int
    count = stoi(buffer);

    //adding the nodes into the tree
    for (int i = 0; i < count; i++) {
        getline(inFile, buffer);
        //getline from a string as if it was a input file
        stringstream ss(buffer);

        //reading in the key
        string organ;
        getline(ss, organ, ';');

        //while file hasn't ended
        while(!ss.eof()) {
            string doc, freqStr;

            //reading the document until ',' and the am with frequency with ';'
            getline(ss, doc, ',');
            getline(ss, freqStr, ';');

            //counting the frequency
            int freq = stoi(freqStr);

            //inserting the word into tree word, document found in, and frequency
            orgs.insert(organ, doc, freq);
        }
    }
    inFile.close();
}

void indexHandler::addDocCount(string doc) {
    if(docCounts.find(doc) == docCounts.end()) {
        //if the doc was never seen before
        docCounts[doc] = 1;
    }
}

int indexHandler::getDocCount(string doc) {
    return docCounts[doc];
}


