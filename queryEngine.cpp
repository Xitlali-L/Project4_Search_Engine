//
// Created by Xital on 11/14/2024.
//

#include "queryEngine.h"

queryEngine::queryEngine() {
    iH = nullptr;
}

void queryEngine::setIndexHandler(indexHandler *i) {
    iH = i;
}

vector<pair<double, string>> queryEngine::parseQuery(string query) {
    stringstream ss(query);
    //terms we need to serach for in the tree
    vector<string>terms;
    while(!ss.eof()) {
        string temp;
        //tokenizing the terms
        getline(ss, temp, ' ');
        //storing it in the vector
        terms.push_back(temp);
    }
    trim(terms[0]);
    stem(terms[0]);
    //returns search results but first getting the term from the index handler
    map<string, int> searchResults = iH-> getWord(terms[0]);
    for(int i = 1; i <terms.size(); i++) {
        if(terms[i][0] == '-') {
            //grabs the words from the text except the first term
            string word = terms[i].substr(1, terms[i].length() - 1);
            trim(word);
            stem(word);
            //creating a map just for the search results of the word
            map<string, int> docs = iH->getWord(word);
            //comparing and removing any specific words in docs from searchResults
            for(const pair<string, int>& itr : docs) {
                if(searchResults.find(itr.first) != searchResults.end()) {
                    searchResults.erase(itr.first);
                }
            }
        } //checking if the word is greater than 4 and if it starts with ORG:
        //then it is classified as a organization
        else if(terms[i].length() > 4 && terms[i].substr(0, 4) == "ORG:") {
            //removing the org: from the word
            string org = terms[i].substr(4, terms[i].length() - 4);
            trim(org);
            stem(org);
            //getting the documents that contain the organization
            map<string, int> docs = iH->getOrg(org);
            //iterating through the results
            for(const pair<string, int> itr: searchResults) {
                //checking if doc from the result is in the list of documents from the OrgTree
                //if the results don't intersect remove it
                if(docs.find(itr.first) == docs.end()) {
                    searchResults.erase(itr.first);
                }
                else {
                    //if it is in the intersection then add the frequency
                    searchResults[itr.first] = docs[itr.first];
                }
            }
        }

        else if(terms[i].length() > 7 && terms[i].substr(0, 7) == "PERSON:") {
            //removing the person: from the word
            string persons = terms[i].substr(7, terms[i].length() - 7);
            trim(persons);
            stem(persons);
            //getting the documents that contain the organization
            map<string, int> docs = iH->getPpl(persons);
            //iterating through the results
            for(const pair<string, int> itr: searchResults) {
                //checking if doc from the result is in the list of documents from the PPLTree
                //if the results don't intersect remove it
                if(docs.find(itr.first) == docs.end()) {
                    searchResults.erase(itr.first);
                }
                else {
                    //if it is in the intersection then add the frequency
                    searchResults[itr.first] = docs[itr.first];
                }
            }
        }

        else {
            string word = terms[i];
            trim(word);
            stem(word);
            //getting the documents that contain the organization
            map<string, int> docs = iH->getWord(word);
            //iterating through the results
            for(const pair<string, int> itr: searchResults) {
                //checking if doc from the result is in the list of documents from the PPLTree
                //if the results don't intersect remove it
                if(docs.find(itr.first) == docs.end()) {
                    searchResults.erase(itr.first);
                }
                else {
                    //if it is in the intersection then add the frequency
                    searchResults[itr.first] = docs[itr.first];
                }
            }
        }
    }
    return sortRelevancy(searchResults);
}

//parameter is the map of unsorted documents and we're going to place them in a vector with a tdfidf
vector<pair<double, string>> queryEngine::sortRelevancy(map<string, int> & results) {
    //where our output would go
    vector<pair<double, string>> sortedResults;
    //iterate over the documents
    //calling the getDocCount to calculate the relevancy
    for(const pair<string, int>& itr : results) {
        double relevancy = (double)(itr.second)/(iH->getDocCount(itr.first));
        //pushes our output into the vector (sorted doc and its relevancy)
        sortedResults.push_back(make_pair(relevancy, itr.first));
    }
    //sorting our relevancy
    return mergeSort(sortedResults);
}

vector<pair<double, string>> queryEngine::mergeSort(vector<pair<double, string>> & vec) {
//base case
    if(vec.size() <= 1) {
        return vec;
    }
    int mid = vec.size() / 2;
    //creating the two sub arrays by splitting them until the mid point
    vector<pair<double, string>> left(vec.begin(), vec.begin() + mid);
    vector<pair<double, string>> right(vec.begin() + mid, vec.end());
    //recurrsive calls
    left = mergeSort(left);
    right = mergeSort(right);
    //putting them back together
    return merge(left, right);
}

vector<pair<double, string>> queryEngine::merge(vector<pair<double, string>> & left, vector<pair<double, string>> & right) {
//itr1 goes through left vector and itr2 goes through right vector
    int itr1 = 0, itr2 = 0;
    vector<pair<double, string>> vec;
    while(itr1 < left.size() & itr2 < right.size()) {
        //have a descending form to have the most relevent in the first
        if(left[itr1] > right[itr2]) {
            vec.push_back(left[itr1]);
            itr1++;
        }
        else {
            vec.push_back(right[itr2]);
            itr2++;
        }
    }
//going to the end of the left vector in case we haven't reached it
//if the end of the left vector isn't reached push back the remaining vector
    while(itr1 < left.size()) {
        vec.push_back(left[itr1]);
        itr1++;
    }
    //going to the end of the right vector in case we haven't reached it
    while(itr2 < right.size()) {
        vec.push_back(right[itr2]);
        itr2++;
    }
    return vec;
}








