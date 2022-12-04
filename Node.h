#ifndef ADT_BALANCEDTREE_NODE_H
#define ADT_BALANCEDTREE_NODE_H

template <typename T>
class Node {
public:
    Node() : son1(nullptr), son2(nullptr), son3(nullptr), low2(-1), low3(-1), key(-1) {}
    Node(T k, T d) : low2(-1), low3(-1), son1(nullptr), son2(nullptr), son3(nullptr), key(k), data(d) {}

    Node *son1, *son2, *son3;
    T low2, low3;
    T key;
    T data;
};
#endif //ADT_BALANCEDTREE_NODE_H
