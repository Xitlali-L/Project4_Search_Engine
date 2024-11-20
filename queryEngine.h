//
// Created by Xitlali on 11/14/2024.
//

#ifndef QUERYENGINE_H
#define QUERYENGINE_H
#include "indexHandler.h"
#include "porter2_stemmer.h"
using namespace Porter2Stemmer;

class queryEngine {
private:
    indexHandler* iH;

public:
    queryEngine();
    void setIndexHandler(indexHandler* i);
    //users text search and returns text that is the more relevant
    vector<pair<double, string>>parseQuery(string query);
    //returning a sorted list of search results from a unsorted map
    vector<pair<double,string>> sortRelevancy(map<string, int>&);
    //search results and their relevancy scores
    vector<pair<double, string>> mergeSort(vector<pair<double, string>>&);
    vector<pair<double, string>> merge(vector<pair<double, string>> &, vector<pair<double, string>>&);



};



#endif //QUERYENGINE_H
