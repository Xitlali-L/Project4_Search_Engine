//
// Created by Xital on 11/13/2024.
//

#ifndef DOCPARSER_H
#define DOCPARSER_H
#include "indexHandler.h"
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <filesystem>  //traverse files to find files names
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace rapidjson;
using namespace Porter2Stemmer;

struct DocInfo{
    string title;
    string publication;
    string date;
    string text;
};

class DocParser {
private:
    indexHandler* iH;
    //hash-unordered
    unordered_set<string> stopwords;

public:
    DocParser();
    //****DON'T NEED TO DO RULE OF THREE CUZ ITS A SHALLOW COPY****
    void setIndex(indexHandler*);
    void readStopWords();
    //going to look through the folder for json file we want to read
    void readFolder(string);
    //called when a json file is needed to be read
    void parseJson(string);

    //function is collecting data(the ones in DocInfo) and locating the info in a file
    DocInfo getDocData(string);
};



#endif //DOCPARSER_H
