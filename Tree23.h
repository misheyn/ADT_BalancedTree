#ifndef ADT_BALANCEDTREE_TREE23_H
#define ADT_BALANCEDTREE_TREE23_H

#include <iostream>
#include "Node.h"
#include "ForwardIterator.h"
#include "ReverseIterator.h"

using namespace std;

template<typename T>
class Tree23 {
public:
    friend class ForwardIterator<T>;

    friend class ReverseIterator<T>;

    Tree23();

    ~Tree23();

    Tree23(Tree23 &obj);

    int getSize();

    bool clear();

    bool isEmpty();

    T getValue(T k);

    bool changeValue(T k, T d);

    bool insert(T k, T d);

    bool remove(T k);

    void printTree();

    int getStat();

    ForwardIterator<T> begin() {
        return ForwardIterator(root, 1);
    }

    ForwardIterator<T> end() {
        return ForwardIterator(root, -1);
    }

    ReverseIterator<T> rbegin() {
        return ReverseIterator(root, 1);
    }

    ReverseIterator<T> rend() {
        return ReverseIterator(root, -1);
    }

private:
    int count;
    Node<T> *root;
    int stat;

    bool doInsert(Node<T> **node, T k, T d);

    bool doRemove(Node<T> **node, T k);

    bool doInsert1(Node<T> **node, Node<T> *leaf, Node<T> **tmp, T *k);

    bool doRemove1(Node<T> **node, T k, Node<T> **tlow1, bool *one);

    bool isLeaf(Node<T> *node);

    void print(Node<T> *node, int lvl);

    void destructor(Node<T> *node);

    T search(Node<T> *node, T k, T *val);

    bool write(Node<T> *node, T k, T d, bool *f);
};


#endif //ADT_BALANCEDTREE_TREE23_H
