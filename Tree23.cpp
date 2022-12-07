#include "Tree23.h"

using namespace std;

template<typename T>
Tree23<T>::Tree23() {
    root = nullptr;
    count = 0;
    stat = 0;
}

template<typename T>
Tree23<T>::~Tree23() {
    destructor(root);
}

template<typename T>
void Tree23<T>::destructor(Node<T> *node) {
    if (node != nullptr) {
        if (!node->son1) destructor(node->son1);
        if (!node->son2) destructor(node->son2);
        if (!node->son3) destructor(node->son3);

        delete node;
    }
}

template<typename T>
Tree23<T>::Tree23(Tree23 &obj) {
    root = obj.root;
    count = obj.count;
}

template<typename T>
int Tree23<T>::getSize() {
    return count;
}

template<typename T>
bool Tree23<T>::clear() {
    bool flag;
    while (root != nullptr) flag = doRemove(&root, root->key);
    return flag;
}

template<typename T>
bool Tree23<T>::isEmpty() {
    if (root == nullptr) return true;
    else return false;
}

template<typename T>
bool Tree23<T>::insert(T k, T d) {
    count++;
    stat = 0;
    return doInsert(&root, k, d);
}

template<typename T>
bool Tree23<T>::doInsert(Node<T> **node, T k, T d) {
    auto lt = new Node<T>(k, d);
    if ((*node) == nullptr) {
        (*node) = new Node<T>();
        (*node)->son1 = lt;
        return true;
    }
    if ((*node)->son2 == nullptr) {
        if ((*node)->son1->key < k) {
            (*node)->son2 = lt;
            (*node)->low2 = k;
            return true;
        } else if ((*node)->son1->key > k) {
            (*node)->son2 = (*node)->son1;
            (*node)->low2 = (*node)->son1->key;
            (*node)->son1 = lt;
            return true;
        } else {
            delete lt;
            return false;
        }
    }
    Node<T> *tmp;
    T k2;
    bool inserted = doInsert1(node, lt, &tmp, &k2);
    if (!inserted) {
        delete lt;
        return false;
    }
    if (tmp != nullptr) {
        auto temp = (*node);
        *node = new Node<T>();
        (*node)->son1 = temp;
        (*node)->son2 = tmp;
        (*node)->son3 = nullptr;
        (*node)->low2 = k2;
        (*node)->son1->low3 = -1;
    }
    return true;
}

template<typename T>
bool Tree23<T>::doInsert1(Node<T> **node, Node<T> *leaf, Node<T> **tmp, T *k) {
    stat++;
    *tmp = nullptr;
    if (*node == nullptr) return false;
    if (isLeaf(*node)) {
        if ((*node)->key == leaf->key) return false;
        else *tmp = leaf;
        if ((*node)->key < leaf->key) {
            *k = leaf->key;
        } else {
            *k = (*node)->key;
            T temp1 = (*node)->key;
            (*node)->key = leaf->key;
            leaf->key = temp1;
            T temp2 = (*node)->data;
            (*node)->data = leaf->data;
            leaf->data = temp2;
        }
        return true;
    }
    int child;
    Node<T> *w;

    if (leaf->key < (*node)->low2) {
        child = 1;
        w = (*node)->son1;
    } else if ((*node)->son3 == nullptr || ((*node)->son3 != nullptr && leaf->key < (*node)->low3)) {
        child = 2;
        w = (*node)->son2;
    } else {
        child = 3;
        w = (*node)->son3;
    }
    Node<T> *tmp1 = nullptr;
    T k3;
    bool inserted = doInsert1(&w, leaf, &tmp1, &k3);
    if (inserted) {
        if (tmp1 != nullptr) {
            if ((*node)->son3 == nullptr) {
                if (child == 2) {
                    (*node)->son3 = tmp1;
                    (*node)->low3 = k3;
                } else {
                    (*node)->son3 = (*node)->son2;
                    (*node)->low3 = (*node)->low2;
                    (*node)->son2 = tmp1;
                    (*node)->low2 = k3;
                }
            } else {
                *tmp = new Node<T>();
                if (child == 3) {
                    (*tmp)->son1 = (*node)->son3;
                    (*tmp)->son2 = tmp1;
                    (*tmp)->son3 = nullptr;
                    (*tmp)->low2 = k3;
                    (*node)->son3 = nullptr;
                    *k = (*node)->low3;
                    (*node)->low3 = -1;
                } else {
                    (*tmp)->son2 = (*node)->son3;
                    (*tmp)->low2 = (*node)->low3;
                    (*tmp)->son3 = nullptr;
                }
                if (child == 2) {
                    (*tmp)->son1 = tmp1;
                    *k = k3;
                }
                if (child == 1) {
                    (*tmp)->son1 = (*node)->son2;
                    (*node)->son2 = tmp1;
                    *k = (*node)->low2;
                    (*node)->low2 = k3;
                    (*node)->son3 = nullptr;
                }
            }
        }
    }
    return inserted;
}

template<typename T>
bool Tree23<T>::isLeaf(Node<T> *node) {
    if (node != nullptr) return node->key != -1;
    else return false;
}

template<typename T>
void Tree23<T>::print(Node<T> *node, int lvl) {
    if (node != nullptr) {
        if (isLeaf(node)) {
            cout << node->key << ":" << node->data << "   " << endl;
        } else {
            cout << "Level " << lvl << "  " << node->low2 << " " << node->low3 << endl;
            print(node->son1, lvl + 1);
            print(node->son2, lvl + 1);
            print(node->son3, lvl + 1);
        }
    }
}

template<typename T>
void Tree23<T>::printTree() {
    int level = 1;
    print(root, level);
}

template<typename T>
bool Tree23<T>::remove(T k) {
    count--;
    stat = 0;
    return doRemove(&root, k);
}

template<typename T>
bool Tree23<T>::doRemove(Node<T> **node, T k) {

    if (*node == nullptr) return false;
    if ((*node)->son2 == nullptr) {
        if ((*node)->son1->key == k) {
            delete (*node)->son1;
            (*node)->son1 = nullptr;
            delete *node;
            *node = nullptr;
            return true;
        } else {
            return false;
        }
    }
    Node<T> *tmin = nullptr;
    bool one;
    bool deleted = doRemove1(node, k, &tmin, &one);
    if (deleted) {
        if (one) {
            if (!isLeaf((*node)->son1)) {
                auto tmp = (*node)->son1;
                delete *node;
                *node = tmp;
            }
        }
    }
    return deleted;
}

template<typename T>
bool Tree23<T>::doRemove1(Node<T> **node, T k, Node<T> **tlow1, bool *one) {
    stat++;
    *tlow1 = nullptr;
    *one = false;
    if (*node == nullptr) return false;
    if (isLeaf((*node)->son1)) {
        if ((*node)->son1->key == k) {
            delete (*node)->son1;
            (*node)->son1 = (*node)->son2;
            (*node)->son2 = (*node)->son3;
            (*node)->son3 = nullptr;
            (*node)->low2 = (*node)->low3;
        } else if ((*node)->son2->key == k) {
            delete (*node)->son2;
            (*node)->son2 = (*node)->son3;
            (*node)->son3 = nullptr;
            (*node)->low2 = (*node)->low3;
        } else if ((*node)->son3 != nullptr && (*node)->son3->key == k) {
            delete (*node)->son3;
            (*node)->son3 = nullptr;
        } else {
            return false;
        }
        *tlow1 = (*node)->son1;
        if ((*node)->son2 == nullptr) {
            *one = true;
            return true;
        }
    }
    int child;
    Node<T> *w = nullptr;
    if (k < (*node)->low2) {
        child = 1;
        w = (*node)->son1;
    } else if ((*node)->son3 == nullptr || k < (*node)->low3) {
        child = 2;
        w = (*node)->son2;
    } else {
        child = 3;
        w = (*node)->son3;
    }
    Node<T> *tlow2 = nullptr;
    bool one2;
    if (!doRemove1(&w, k, &tlow2, &one2)) return false;
    *tlow1 = tlow2;
    if (tlow2 != nullptr) {
        if (child == 2) {
            (*node)->low2 = tlow2->key;
            *tlow1 = nullptr;
        }
        if (child == 3) {
            (*node)->low3 = tlow2->key;
            *tlow1 = nullptr;
        }
    }
    if (!one2) return true;
    Node<T> *tmp;
    if (child == 1) {
        tmp = (*node)->son2;
        if (tmp->son3 != nullptr) {
            w->son2 = tmp->son1;
            w->low2 = (*node)->low2;
            (*node)->low2 = tmp->low2;
            tmp->son1 = tmp->son2;
            tmp->son2 = tmp->son3;
            tmp->low2 = tmp->low3;
            tmp->son3 = nullptr;
        } else {
            tmp->son3 = tmp->son2;
            tmp->low3 = tmp->low2;
            tmp->son2 = tmp->son1;
            tmp->low2 = (*node)->low2;
            tmp->son1 = w->son1;
            delete w;
            (*node)->son1 = (*node)->son2;
            (*node)->son2 = (*node)->son3;
            (*node)->low2 = (*node)->low3;
            (*node)->son3 = nullptr;
        }
        if ((*node)->son2 == nullptr) {
            *one = true;
            return true;
        }
    }
    if (child == 2) {
        tmp = (*node)->son1;
        if (tmp->son3 != nullptr) {
            w->son2 = w->son1;
            w->low2 = (*node)->low2;
            w->son1 = tmp->son3;
            tmp->son3 = nullptr;
            (*node)->low2 = tmp->low3;
            return true;
        } else {
            Node<T> *tmp1 = (*node)->son3;
            if (tmp1 != nullptr && tmp1->son3 != nullptr) {
                w->son2 = tmp1->son1;
                w->low2 = (*node)->low3;
                (*node)->low3 = tmp1->low2;
                tmp1->son1 = tmp1->son2;
                tmp1->son2 = tmp1->son3;
                tmp1->low2 = tmp1->low3;
                tmp1->low3 = -1;
                tmp1->son3 = nullptr;
                return true;
            }
        }
        tmp->son3 = w->son1;
        tmp->low3 = (*node)->low2;
        delete w;
        (*node)->son2 = (*node)->son3;
        (*node)->low2 = (*node)->low3;
        (*node)->son3 = nullptr;
        if ((*node)->son2 == nullptr) {
            *one = true;
            return true;
        }
    }
    if (child == 3) {
        tmp = (*node)->son2;
        if (tmp->son3 != nullptr) {
            w->son2 = w->son1;
            w->son1 = w->son3;
            (*node)->low2 = tmp->low3;
            tmp->son3 = nullptr;
        } else {
            tmp->son3 = w->son1;
            tmp->low3 = (*node)->low3;
            (*node)->low3 = -1;
            (*node)->son3 = nullptr;
            delete w;
        }
    }
    return true;
}

template<typename T>
T Tree23<T>::getValue(T k) {
    stat = 0;
    T val = -1;
    search(root, k, &val);
    return val;
}

template<typename T>
T Tree23<T>::search(Node<T> *node, T k, T *val) {
    if (node == nullptr) return -1;
    stat++;
    if (isLeaf(node)) {
        if (node->key == k) *val = node->data;
    } else {
        if (k < node->low2) search(node->son1, k, val);
        else if (node->low3 != -1 && k >= node->low3) search(node->son3, k, val);
        else search(node->son2, k, val);
    }
    return *val;
}

template<typename T>
bool Tree23<T>::changeValue(T k, T d) {
    bool f = false;
    write(root, k, d, &f);
    return f;
}

template<typename T>
bool Tree23<T>::write(Node<T> *node, T k, T d, bool *f) {
    if (node == nullptr) return false;
    if (isLeaf(node)) {
        if (node->key == k) {
            node->data = d;
            *f = true;
        }
    } else {
        if (k < node->low2) write(node->son1, k, d, f);
        else if (node->low3 != -1 && k >= node->low3) write(node->son3, k, d, f);
        else write(node->son2, k, d, f);
    }
    return *f;
}

template<typename T>
int Tree23<T>::getStat() {
    int tmp = stat;
    stat = 0;
    return tmp;
}

template
class Tree23<int>;

template
class Tree23<unsigned long long>;