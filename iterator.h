#ifndef CACHELIST_ITERATOR_H
#define CACHELIST_ITERATOR_H
#pragma once
#include "Node.h"


// Iterator is a point to Node
class Iterator {
public:
    Node* address = nullptr;

    Iterator() = default;
    Iterator(Node* address) {
        this->address = address;
    }

    Iterator& operator=(const Iterator &iterator) = default;

    // returns Node after Node that it point
    // if Iterator point to the last Node in the list, returns last Node (so himself)
    Iterator getNext() const {
        if(this->address->next == nullptr)
            return *this;
        return this->address->next;
    }

    // returns Node before Node that it point
    // if Iterator point to the first Node in the list, returns first Node (so himself)
    Iterator getPrevious() const {
        if(this->address->prev == nullptr)
            return *this;
        return this->address->prev;
    }
};

#endif //CACHELIST_ITERATOR_H