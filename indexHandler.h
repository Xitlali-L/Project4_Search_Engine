//
// Created by Xitlali on 11/12/2024.
//

#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "AVLTree.h"
#include <fstream>  //reading and wirting files with persistence
#include <sstream> //sstring streams we'll use for parsing (persistence)
#include <iostream>



//shared data that the query and index access (holds getters and setter and persistance)
class indexHandler {
private:
    //key is a string (individual words), and the value is the file name for doc
    //map has everything we need if user searches for a word
    AVLTree<string, string> words;
    //map for people
    AVLTree<string, string> ppl;
    //map for organizations
    AVLTree<string, string> orgs;

public:
    //setter for adding word
    void addWord(string word, string doc) {
        words.insert(word, doc);
    }

    //returning the word
    map<string,int> getWord(string word) {
        return words.getnode(word);
    }

    //setter for adding people
    void addPpl(string word, string doc) {
        ppl.insert(word, doc);
    }

    //returning the people
    map<string,int> getPpl(string word) {
        return ppl.getnode(word);
    }

    //setter for adding organizations
    void addOrg(string word, string doc) {
        orgs.insert(word, doc);
    }

    //returning the organizations
    map<string,int> getOrg(string word) {
        return orgs.getnode(word);
    }

    //creating the persistence (save progress)
    void makePersist();
    //reading the persistence to populate trees
    void readPersist();
};



#endif //INDEXHANDLER_H
