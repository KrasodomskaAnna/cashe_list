#ifndef CACHELIST_NODE_H
#define CACHELIST_NODE_H
#pragma once

// Node is an element of the list, that stores his value and pointers to previous and next Node
class Node {
public:
    Node* next = nullptr;
    Node* prev = nullptr;
    unsigned long long int value = 0;
    Node() = default;
};


#endif //CACHELIST_NODE_H
