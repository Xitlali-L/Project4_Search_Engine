//
// Created by Xital on 11/13/2024.
//

#include "DocParser.h"

//default values
DocParser::DocParser() {
    readStopWords();
    iH = nullptr;
}

//shallow copy of the indexHandler pointer
void DocParser::setIndex(indexHandler * i) {
    iH = i;
}

void DocParser::readStopWords() {
    //read file
    ifstream inFile ("../stopwords.txt");
    if(!inFile.is_open()) {
        cout << "ERROR failed to open stopWords file" << endl;
        exit(1);
    }
    //in case something is in the hash table we clear it
    stopwords.clear();
    //if no end of file
    while(!inFile.eof()) {
        string word;
        //reading in one word from the stopword file
        getline(inFile, word);
        //if no more words then it ends file
        if(word.empty()) {
            break;
        }
        //adding the words into the set
        //removes white space at the ends of the words
        trim(word);
        //stemming the words (cutting sufixs)
        stem(word);
        stopwords.insert(word);
    }
    inFile.close();
}

//open archive folder and get the json files
void DocParser::readFolder(string folder) {
    //creating an iterator
    auto itr = filesystem::recursive_directory_iterator(folder);
    //using itr to file all the files in the folder
    for(const auto& file: itr) {
        //checks to make sure it is a file and not a folder and that it ends in .json
        if(file.is_regular_file() && file.path().extension().string() == ".json") {
            parseJson(file.path().string());
        }
    }


}

void DocParser::parseJson(string fileName) {
ifstream inFile(fileName);
    if(!inFile.is_open()) {
        cout << "ERROR failed to open file" << fileName << endl;
        exit(1);
    }

    //takes a ifstream and convert it into a json stream
    IStreamWrapper isw(inFile);
    //object file document
    Document doc;
    doc.ParseStream(isw);
    string text = doc["text"].GetString();
    //creates a pattern to parse the text
    //A through Z and a through z
    regex pattern("[A-Za-z]+");
    //beginning of the text, end of text and the pattern it will use on  the text
    sregex_token_iterator itr(text.begin(), text.end(), pattern);
    //creating a variable for the end of the text
    sregex_token_iterator end;

    //adding parsed words into AVLTree
    //while there are still matches in the text
    while(itr != end) {
        //tokenizing the words and adding them to the AVLTree
        //getting the value by dereferencing the itr
        string token = *itr;
        trim(token);
        stem(token);
        //if the word isnt a stop word we call our index handeler
        if(stopwords.find(token) == stopwords.end()) {
            iH -> addWord(token, fileName);
        }
        //go to the next word that matches the pattern
        itr++;
    }

    //adding parsed people into AVLTree
    auto people = doc["entities"]["persons"].GetArray();
    //represents one person
    for(const auto& person : people) {
        //creating a stringstream to parse to spilt name
        stringstream ss (person["name"].GetString());

        //while not end of file
        while(!ss.eof()) {
            string name;
            //getting the name up until the delimiter and then adding whatever there was into the string name
            getline(ss, name, ' ');
            trim(name);
            stem(name);

            if(!name.empty()) {
                //if name not empty then we'll add to the AVLtree
                iH->addPpl(name, fileName);
            }
        }
    }


    //adding parsed organizations into AVLTree
    auto orga = doc["entities"]["organizations"].GetArray();
    //represents one person
    for(const auto& orgniz : orga) {
        //creating a stringstream to parse to spilt name
        stringstream ss (orgniz["name"].GetString());

        //while not end of file
        while(!ss.eof()) {
            string name;
            //getting the name up until the delimiter and then adding whatever there was into the string name
            getline(ss, name, ' ');
            trim(name);
            stem(name);

            if(!name.empty()) {
                //if name not empty then we'll add to the AVLtree
                iH->addOrg(name, fileName);
            }
        }
    }
    //closing file
    inFile.close();
}

DocInfo DocParser::getDocData(string  path) {
    ifstream inFile(path);
    if(!inFile.is_open()) {
        cout << "ERROR failed to open file" << path << endl;
        exit(1);
    }
    IStreamWrapper isw(inFile);
    Document doc;
    doc.ParseStream(isw);
    DocInfo dc;
    //grabbing our info from the json files and storing it in the docInfo object
    dc.title = doc["title"]. GetString();
    dc.publication = doc["thread"]["site"].GetString();
    dc.date = doc["published"].GetString();
    dc.text = doc["text"].GetString();

    inFile.close();
    return dc;

}




