// intbst.cpp
// Implements class IntBST
// Neil Gadagkar, April 23, 2024

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() {
    root = nullptr; 

}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);

}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(n){
        clear(n->left);
        clear(n->right);
        delete n;
    }

}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root){
        root = new Node(value); 
        return true;
    }
    return insert(value, root);

}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value < n->info){
        if(!n->left){
            n->left = new Node(value);
            return true;
        }
        else{
            return insert(value, n->left);
        }
    }
    else if(value > n->info){
        if(!n->right){
            n->right = new Node(value);
            return true;
        }
        else{
            return insert(value, n->right);
        }
    }
    else{
        return false;
    
}
}   

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n){
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n){
        return; 
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}
// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n){
        return n->info + sum(n->left) + sum(n->right);
    }
    return 0;
}
// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n){
        return 0;
    }
    return count(n->left) + count(n->right) + 1;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    while(n){
        if(value == n->info){
            return n;
        }
        if(value > n->info){
            n = n->right;
        }
        else{
            n = n->left;
        }
    }
    return nullptr;
    
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* n = root;
    while(n){
        if(value == n->info){
            return true;
        }
        if(value > n->info){
            n = n->right;
        }
        else{
            n = n->left;
        }
    }
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
   Node* current = root;
   Node* predecessor = nullptr;
    while(current){
        if(value == current -> info){
            if(current -> left){
                Node* temp = current ->left;
                while(temp->right){
                    temp = temp->right;
                }
                predecessor = temp;
            }
            break;

        }
        else if(value > current->info){
            predecessor = current;
            current = current -> right;
        }
        
        else{
            current = current->left;
        }
    }
    return predecessor;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* current = root;
   Node* predecessor = nullptr;
    while(current){
        if(value == current -> info){
            if(current -> left){
                Node* temp = current ->left;
                while(temp->right){
                    temp = temp->right;
                }
                predecessor = temp;
            }
            break;

        }
        else if(value > current->info){
            predecessor = current;
            current = current -> right;
        }
        
        else{
            current = current->left;
        }
    }
    if(predecessor){
        return predecessor->info;
    }
    return 0;
}


// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* current = root;
    Node* successor = nullptr; 
    while(current){
        if(value == current -> info){
            if(current->right){
                Node* temp = current->right;
                while(temp->left){
                    temp = temp->left;
                }
                successor = temp;
            }
            break;
        }

        else if(value < current->info){
            successor = current;
            current = current->left;
        }
        else{
            current = current->right;
        }

    }
    return successor;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* current = root;
    Node* successor = nullptr; 
    while(current){
        if(value == current -> info){
            if(current->right){
                Node* temp = current->right;
                while(temp->left){
                    temp = temp->left;
                }
                successor = temp;
            }
            break;
        }
        else if(value < current->info){
            successor = current;
            current = current->left;
        }
        else{
            current = current->right;
        }

    }
    if(successor){
        return successor->info;
    }
    
    return 0;

}


// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist

bool IntBST::remove(int value) {
Node* nodeToDelete = getNodeFor(value, root);
if (!nodeToDelete) return false;  


if (nodeToDelete->left && nodeToDelete->right) {
    Node* successor = getSuccessorNode(value);
    nodeToDelete->info = successor->info;  
    nodeToDelete = successor;              
}


Node* child = (nodeToDelete->left) ? nodeToDelete->left : nodeToDelete->right;

if (child) {
    child->parent = nodeToDelete->parent;
}

if (!nodeToDelete->parent) {
    root = child;  
} else if (nodeToDelete == nodeToDelete->parent->left) {
    nodeToDelete->parent->left = child;
} else {
    nodeToDelete->parent->right = child;
}

delete nodeToDelete;
return true;
}
