//
// Created by Xital on 11/11/2024.
//

#ifndef TEMPLATING_H
#define TEMPLATING_H
#include <map>
#include <ostream>
using namespace std;

template<typename key, typename value>
class AVLTree {
private:
    //creating a class for a avlnode
    struct AVLNode {
        //k represents a person from an org
        key k;
        //conDoc the number of times k is found in a document
        map<value, int> conDoc;
        AVLNode* left;
        AVLNode* right;
        //height is the level in the tree
        int height;
        //(node for one key)//
        //creating a constructor with the default setting for a node (AKA root node)
        AVLNode(key k, AVLNode* l = nullptr, AVLNode* r = nullptr, int h = 0) {
            //setting every variable with its start values
            this-> k = k;
            this->left = l;
            this->right = r;
            this->height = h;
        }
    };

    AVLNode* root;
    //number of nodes
    int size;
    void clear(AVLNode* &);
    map<key, int> getNode(const key &, AVLNode* &);
    void insert(const key &, const value &, AVLNode* &);
    void balance(AVLNode* &);
    int height(AVLNode* &);
    void clone(AVLNode* &, AVLNode* &);
    void printTree(ostream &, AVLNode* &);
    void rotateLeft(AVLNode* &);
    void rotateDoubleLeft(AVLNode* &);
    void rotateRight(AVLNode* &);
    void rotateDoubleRight(AVLNode* &);
    void insert(key, value, int, AVLNode* &);

public:
    AVLTree();
    //RULE OF THREE:
    //Copy constructor
    AVLTree(const AVLTree &);
    //assignment constructor
    AVLTree operator=(const AVLTree &);
    //deconstructor
    ~AVLTree();
    void clear();
    map<value, int> getnode(const key &);
    //a userview insert function: that calls the private insert function to recursively
    void insert(const key &, const value &);
    int getSize();
    void printTree(ostream &);
    void insert(key, value, int);
};


//private functions

template<typename key, typename value>
void AVLTree<key, value>::clear(AVLNode *& node) {
    //base case:
    if(node = nullptr) {
        return;
    }
    //action - deleting the node (post-order transversal)
    clear(node->left);
    clear(node->right);
    delete node;

}

template<typename key, typename value>
//if key matches then return node
map<key, int> AVLTree<key, value>::getNode(const key & k, AVLNode *& node) {
    //there is a key and value but need to create a node
    if(node == nullptr) {
        return map<value, int>();
    }
    //returning recursive call
    else if(k < node->k) {
        return getnode(k,node->left);
    }
    else if(k > node->k) {
        return getnode(k, node->right);
    }
    //else return conDoc map
    else {
        return node->conDoc;
    }
}

template<typename key, typename value>
void AVLTree<key, value>::insert(const key & k, const value & v, AVLNode *& node) {
    //there is a key and value but need to create a node
    if(node == nullptr) {
        node = new AVLNode(k);
        //setting it to one because it's the first time were seeing this word
        node->conDoc[v] = 1;
        //increasing the size because we created a new node
        size++;
    }
    //placing the new node wither on the left or the right branch
    else if(k < node->k) {
        insert(k, v, node->left);
    }
    else if(k > node->k) {
        insert(k, v, node->right);
    }
    //else there is already a key match so we just set it
    else {
        //find the value and end search then initialize to 1
        if(node->conDoc.find(v) == node->conDoc.end()) {
            node->conDoc[v] = 1;
        }
        //or incement the count
        else {
            node->conDoc[v]++;
        }
    }
    balance(node);
}

template<typename key, typename value>
void AVLTree<key, value>::balance(AVLNode *& node) {
    //base case
    if(node != nullptr) {
        //checking if the left side is unbalanced by checking if the cound is greater than 1
        if(height(node->left) - height(node->right) > 1) {
            //checking if its left or double left (by checking the height)
            if(height(node->left->left) >= height(node->left->right)) {
                rotateLeft(node);
            }
            else {
                rotateDoubleLeft(node);
            }
        }
        //right side greater than the left side
        else if(height(node->right) - height(node->left) > 1) {
            if(height(node->right->right) >= height(node->right->left)) {
                rotateRight(node);
            }
            else {
                rotateDoubleRight(node);
            }
        }
        //updating the height of the node after the rotations were made
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

template<typename key, typename value>
int AVLTree<key, value>::height(AVLNode *& node) {
    //in case node is null return no height
    if(node == nullptr) {
        return -1;
    }
    else {
        return node->height;
    }
}

template<typename key, typename value>
//(pre-order to copy parents then childs) curr is empty for now
//copy is the tree were copying from and putting into curr tree
void AVLTree<key, value>::clone(AVLNode *& curr, AVLNode *& copy) {
    if(copy != nullptr) {
        //have the same key and height because it's copying from scratch
        curr = new AVLNode(copy->k, nullptr, nullptr, copy->height);
        curr-> r = copy-> conDOC;
        //the reference lets us go back and do backwards recurrence
        clone(curr->left, copy->left);
        clone(curr->right, copy->right);
        size++;
    }
}

template<typename key, typename value>
void AVLTree<key, value>::printTree(ostream &out, AVLNode *&node) {
    //base case
    if(node != nullptr) {
        //in order traversial
        printTree(out, node->left);
        //print the contents of the map
        //using two delimiters
        out << node->k;

        //going through all the docs with this word and printing the docs and frequency
        //creating a new pair and using a semicolon to seperate pairs
        for(const pair <value, int>& itr : node->conDoc) {
            //document = first and frequencey = second
            out << ";" << itr.first << "," << itr.second;
        }
        out << endl;
        printTree(out, node->right);
    }
}

template<typename key, typename value>
void AVLTree<key, value>::rotateLeft(AVLNode *& node) {
    //shallow copy (reference to existing pointer)
    AVLNode* curr = node->left;
    node->left = curr->right;
    curr->right = node;
    //how many level from the bottom is the node at
    node->height = max(height (node->left), height (node->right)) + 1;
    //similar thing with curr//
    node = curr;
}

template<typename key, typename value>
void AVLTree<key, value>::rotateDoubleLeft(AVLNode *& node) {
    //calling the rotate right and left function to balance
    rotateRight(node->left);
    rotateLeft(node);

}

template<typename key, typename value>
void AVLTree<key, value>::rotateRight(AVLNode *& node) {
    //shallow copy (reference to existing pointer)
    AVLNode* curr = node->right;
    node->right = curr->left;
    curr->left = node;
    //how many level from the bottom is the node at
    node->height = max(height (node->right), height (node->left)) + 1;
    //similar thing with curr//
    node = curr;
}

template<typename key, typename value>
void AVLTree<key, value>::rotateDoubleRight(AVLNode *& node) {
    //calling the rotate right and left function to balance
    rotateLeft(node->right);
    rotateRight(node);
}

template<typename key, typename value>
void AVLTree<key, value>::insert(key k, value val, int f, AVLNode *& node) {
    if(node == nullptr) {
        node = new AVLNode(k);
        node->v[val] = f;
        size++;
    }
    else if(node->k == k) {
        node->v[val] = f;
    }
}




//public functions
//most of the public functions calling its corresponding private function

template<typename key, typename value>
AVLTree<key, value>::AVLTree() {
    size = 0;
    root = nullptr;
}

template<typename key, typename value>
AVLTree<key, value>::AVLTree(const AVLTree &) {
    clone(root, copy.root);
}

template<typename key, typename value>
AVLTree<key, value> AVLTree<key, value>::operator=(const AVLTree &) {
    clear();
    clone(root, copy.root);
    return *this;
}

template<typename key, typename value>
AVLTree<key, value>::~AVLTree() {
    clear();
}

template<typename key, typename value>
void AVLTree<key, value>::clear() {
    clear(root);
}

template<typename key, typename value>
map<value, int> AVLTree<key, value>::getnode(const key &) {
    getnode(root);
}

template<typename key, typename value>
void AVLTree<key, value>::insert(const key &, const value &) {
    insert(root);
}

template<typename key, typename value>
int AVLTree<key, value>::getSize() {
    return size;
}

template<typename key, typename value>
void AVLTree<key, value>::printTree(ostream &out) {
    printTree(out, root);
}

template<typename key, typename value>
void AVLTree<key, value>::insert(key k, value v, int f) {
    insert(k, v, f, root);
}


#endif //TEMPLATING_H
