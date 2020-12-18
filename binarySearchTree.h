// Header File Binary Search Tree

#ifndef H_binarySearchTree
#define H_binarySearchTree
#include <iostream>

#include "binaryTree.h"

using namespace std;

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType> {
   public:
    bool search(const elemType &searchItem) const;
    // Function to determine if searchItem is in the binary
    // search tree.
    // Postcondition: Returns true if searchItem is found in
    //               the binary search tree; otherwise,
    //               returns false.

    void insert(const elemType &insertItem);
    // Function to insert insertItem in the binary search tree.
    // Postcondition: If there is no node in the binary search
    //               tree that has the same info as
    //               insertItem, a node with the info
    //               insertItem is created and inserted in the
    //               binary search tree.

    void deleteNode(const elemType &deleteItem);
    // Function to delete deleteItem from the binary search tree
    // Postcondition: If a node with the same info as deleteItem
    //               is found, it is deleted from the binary
    //               search tree.
    //               If the binary tree is empty or deleteItem
    //               is not in the binary tree, an appropriate
    //               message is printed.

   private:
    void deleteFromTree(nodeType<elemType> *&p);
    // Function to delete the node to which p points is
    // deleted from the binary search tree.
    // Postcondition: The node to which p points is deleted
    //               from the binary search tree.
};

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType &searchItem) const {
    nodeType<elemType> *current;
    bool found = false;

    if (this->root == nullptr)
        cout << "Cannot search an empty tree." << endl;
    else {
        current = this->root;

        while (current != nullptr && !found) {
            if (current->info == searchItem)
                found = true;
            else if (current->info > searchItem)
                current = current->lLink;
            else
                current = current->rLink;
        }  // end while
    }      // end else

    return found;
}  // end search

template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType &insertItem) {
    nodeType<elemType> *current;                 // pointer to traverse the tree
    nodeType<elemType> *trailCurrent = nullptr;  // pointer
                                                 // behind current
    nodeType<elemType> *newNode;  // pointer to create the node

    newNode = new nodeType<elemType>;
    newNode->info = insertItem;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    if (this->root == nullptr)
        this->root = newNode;
    else {
        current = this->root;

        while (current != nullptr) {
            trailCurrent = current;

            if (current->info == insertItem) {
                cout << "The item to be inserted is already ";
                cout << "in the tree -- duplicates are not "
                     << "allowed." << endl;
                return;
            } else if (current->info > insertItem)
                current = current->lLink;
            else
                current = current->rLink;
        }  // end while

        if (trailCurrent->info > insertItem)
            trailCurrent->lLink = newNode;
        else
            trailCurrent->rLink = newNode;
    }
}  // end insert

template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType &deleteItem) {
    nodeType<elemType> *current;       // pointer to traverse the tree
    nodeType<elemType> *trailCurrent;  // pointer behind current
    bool found = false;

    if (this->root == nullptr)
        cout << "Cannot delete from an empty tree." << endl;
    else {
        current = this->root;
        trailCurrent = this->root;

        while (current != nullptr && !found) {
            if (current->info == deleteItem)
                found = true;
            else {
                trailCurrent = current;

                if (current->info > deleteItem)
                    current = current->lLink;
                else
                    current = current->rLink;
            }
        }  // end while

        if (current == nullptr)
            cout << "The item to be deleted is not in the tree." << endl;
        else if (found) {
            if (current == this->root)
                deleteFromTree(this->root);
            else if (trailCurrent->info > deleteItem)
                deleteFromTree(trailCurrent->lLink);
            else
                deleteFromTree(trailCurrent->rLink);
        } else
            cout << "The item to be deleted is not in the tree." << endl;
    }
}  // end deleteNode

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType> *&p) {
    nodeType<elemType> *current;       // pointer to traverse the tree
    nodeType<elemType> *trailCurrent;  // pointer behind current
    nodeType<elemType> *temp;          // pointer to delete the node

    if (p == nullptr)
        cout << "Error: The node to be deleted does not exist." << endl;
    else if (p->lLink == nullptr && p->rLink == nullptr) {
        temp = p;
        p = nullptr;
        delete temp;
    } else if (p->lLink == nullptr) {
        temp = p;
        p = temp->rLink;
        delete temp;
    } else if (p->rLink == nullptr) {
        temp = p;
        p = temp->lLink;
        delete temp;
    } else {
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr) {
            trailCurrent = current;
            current = current->rLink;
        }  // end while

        p->info = current->info;

        if (trailCurrent == nullptr)  // current did not move;
                                      // current == p->lLink; adjust p
            p->lLink = current->lLink;
        else
            trailCurrent->rLink = current->lLink;

        delete current;
    }  // end else
}  // end deleteFromTree

#endif