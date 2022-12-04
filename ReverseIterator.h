#ifndef ADT_BALANCEDTREE_REVERSEITERATOR_H
#define ADT_BALANCEDTREE_REVERSEITERATOR_H

#include "Node.h"
#include <list>

using namespace std;

template<typename T>
class ReverseIterator {
public:
    ReverseIterator(Node<T> *tmp, int f) {
        statusFlag = f;
        node = tmp;
        if (node) fillList(node);
        if (f == 1) it = listTree.begin();
        else if (f == -1) it = listTree.end();
    }

    T &operator*() {
        return (*it)->data;
    }

    ReverseIterator operator++(int) {
        it--;
        return *this;
    }

    ReverseIterator operator--(int) {
        it++;
        return *this;
    }

    friend bool operator==(const ReverseIterator &f, const ReverseIterator &s) {
        return *(f.it) = *(s.it);
    }

    friend bool operator!=(const ReverseIterator &f, const ReverseIterator &s) {
        return *(f.it) != *(s.it);
    }

    int getStatus() {
        return statusFlag;
    }


private:
    Node<T> *node;
    list<Node<T> *> listTree;
    typename list<Node<T> *>::iterator it;
    int statusFlag;


    void fillList(Node<T> *r) {
        if (r == nullptr) return;
        fillList(r->son1);
        if (r->key != -1) listTree.push_front(r);
        fillList(r->son2);
        fillList(r->son3);
    }
};

#endif //ADT_BALANCEDTREE_REVERSEITERATOR_H
