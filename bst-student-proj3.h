#ifndef BST_STUDENT_PROJ3
#define BST_STUDENT_PROJ3

#include "bst-prof-proj3.h"

/* CSI 3334
 * Project 3 -- BST Encryption
 * Filename: bst-student-proj3.cpp
 * Name: Eugene Pak
 * Version 1.6
 * Due: 3/1/24
 * This file contains implementation of the encryption tree given by the professor header
 */

/* ~BSTNode()
 * Destructor for BSTNode, recursively deletes left and right children
 */
template <typename T>
BSTNode<T>::~BSTNode(){
    const BSTNode<T> *leftChild = this->getLeft();
    const BSTNode<T> *rightChild = this->getRight();
    if (leftChild) {
        delete leftChild;
        leftChild = nullptr;
    }
    if (rightChild) {
        delete rightChild;
        rightChild = nullptr;
    }
    this->left = nullptr;
    this->right = nullptr;
    return;
}

/* printPreorder(ostream&, string) const
 * Prints the data of the BSTNode and its children in preorder traversal
 *  parameters:
 *  os, ostream reference for output
 *  indent, string for indentation in the output
 *
 *  return value:
 *
 */
template <typename T>
void BSTNode<T>::printPreorder(ostream &os, string indent) const{
    os << indent << this->data << endl;
    indent += "  ";
    if (this->left){
        this->left->printPreorder(os, indent);
    }
    else {
        os << indent << "NULL" << endl;
    }
    if (this->right){
        this->right->printPreorder(os, indent);
    }
    else {
        os << indent << "NULL" << endl;
    }
    return;
}

/* minNode() const
 * Returns a pointer to the node with the minimum value of the given node
 *  parameters:
 *
 *  return value:
 *  Pointer to the node with the minimum value
 */
template <typename T>
const BSTNode<T>* BSTNode<T>::minNode() const{
    if (!this->left){
        return this;
    }
    BSTNode<T>* temp = this->left;
    while (temp->left){
        temp = temp->left;
    }
    return temp;
}

/* maxNode() const
 * Returns a pointer to the node with the maximum value of the given node
 *  parameters:
 *
 *  return value:
 *  Pointer to the node with the maximum value
 */
template <typename T>
const BSTNode<T>* BSTNode<T>::maxNode() const{
    if (!this->right){
        return this;
    }
    BSTNode<T>* temp = this->right;
    while(temp->right){
        temp = temp->right;
    }
    return temp;
}

/* insert(const T&)
 * Inserts a new node with the given item into the BST
 *  parameters:
 *  item, value to be inserted into the BST
 *
 *  return value:
 *
 */
template <typename T>
void BST<T>::insert(const T &item){
    if (this->root){
        BSTNode<T>* temp = this->root;
        while (true){
            if (!(item < temp->data) && !(temp->data < item)){
                return;
            }
            else if (item < temp->data){
                if (temp->left){
                    temp = temp->left;
                }
                else {
                    temp->left = new BSTNode<T> (item);
                    return;
                }
            }
            else {
                if(temp->right){
                    temp = temp->right;
                }
                else {
                    temp->right = new BSTNode<T> (item);
                    return;
                }
            }
        }
    }
    else {
        this->root = new BSTNode<T> (item);
    }
}

/* remove(const T&)
 * Removes a node with the given item from the BST
 *  parameters:
 *  item, value to be removed from the BST
 *
 *  return value:
 *
 */
template <typename T>
void BST<T>::remove(const T &item){
    if(!this->root){
        return;
    }
    BSTNode<T>* toRemove = this->root;
    BSTNode<T>* parent = nullptr;

    while((toRemove->data < item || item < toRemove->data)
    && (toRemove->right || toRemove->left)){
        if (item < toRemove->data){
            parent = toRemove;
            toRemove = toRemove->left;
        }
        else if (toRemove->data < item){
            parent = toRemove;
            toRemove = toRemove->right;
        }
        if (toRemove == nullptr){
            return;
        }
    }
    if (toRemove == nullptr) {
        return;
    }
    if (!(toRemove->data < item) && !(item < toRemove->data)){
        BSTNode<T>* child;
        if (toRemove->left && toRemove->right){
            BSTNode<T>* toNull = nullptr;
            child = toRemove->right;
            while(child->left){
                toNull = child;
                child = child->left;
            }
            if (toNull){
                if (child->right){
                    toNull->left = child->right;
                }
                else {
                    toNull->left = nullptr;
                }
            }
            child->left = toRemove->left;
            if (child != toRemove->right){
                child->right = toRemove->right;
            }
        }
        else if (toRemove->left){
            child = toRemove->left;
        }
        else if (toRemove->right){
            child = toRemove->right;
        }
        else {
            child = nullptr;
        }
        toRemove->left = nullptr;
        toRemove->right = nullptr;
        if (parent == nullptr){
            this->root = child;
        }
        else if (toRemove == parent->right){
            parent->right = child;
        }
        else if (toRemove == parent->left){
            parent->left = child;
        }
        else {
            this->root = child;
        }
        delete toRemove;
    }
    else {
        return;
    }
}

/* encrypt(const T&) const
 * Encrypts the given item and returns its code path
 *  parameters:
 *      item - value to be encrypted
 *
 *  return value:
 *  Encrypted code path as a string
 *  Returns '?' if item is not in tree
 */
template <typename T>
string EncryptionTree<T>::encrypt(const T &item) const{
    if (!this->root){
        return "?";
    }
    string code;
    const BSTNode<T>* temp = this->root;
    while (true){
        if (!(item < temp->getData()) && !(temp->getData() < item)){
            if (code.empty()){
                code += 'r';
            }
            return code;
        }
        else if (item < temp->getData()){
            if (code.empty()){
                code += 'r';
            }
            if (temp->getLeft()){
                code += '0';
                temp = temp->getLeft();
            }
            else {
                return "?";
            }
        }
        else {
            if (code.empty()){
                code += 'r';
            }
            if (temp->getRight()){
                code += '1';
                temp = temp->getRight();
            }
            else {
                return "?";
            }
        }
    }
}

/* decrypt(const string&) const
 * Decrypts the code path and returns the corresponding item
 *  parameters:
 *  path, code path to be decrypted
 *
 *  return value:
 *  Pointer to the decrypted item
 *  Nullptr if path is invalid
 */
template <typename T>
const T* EncryptionTree<T>::decrypt(const string &path) const{
    if (!this->root){
        return nullptr;
    }
    const BSTNode<T>* temp = this->root;
    for (int i = 0; i < path.length(); i++){
        if(path.at(0) != 'r'){
            return nullptr;
        }
        else if (path.at(i) == '0'){
            if (temp->getLeft()){
                temp = temp->getLeft();
            }
            else {
                return nullptr;
            }
        }
        else if (path.at(i) == '1'){
            if (temp->getRight()){
                temp = temp->getRight();
            }
            else {
                return nullptr;
            }
        }
    }
    return &temp->getData();
}

#endif