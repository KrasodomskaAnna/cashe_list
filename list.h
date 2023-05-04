#ifndef CACHELIST_LIST_H
#define CACHELIST_LIST_H
#pragma once

#include <iostream>
#include "Node.h"
#include "iterator.h"
#include "utils.h"


using namespace std;

// List of elements
class List {
public:
    List() {
        this->allIterators[ITERATORS_NUMBER] = nullptr;
        this->allIterators[ITERATORS_NUMBER+1] = nullptr;
    }

    void init() {};

    // initialise Iterator which is on the position to, that point on the same Node as from
    void initOperator(int to, int from) {
        getIterator(to) = getIterator(from);
    }

    // moves Iterator to point to next Node
    void moveFurtherIterator(int number) {
        getIterator(number) = getIterator(number).getNext();
    }
    // moves Iterator to point to previous Node
    void moveBackwardIterator(int number) {
        getIterator(number) = getIterator(number).getPrevious();
    }

    // prints all Nodes in the list or only Node which is pointed by Iterator number element
    void printElements(char* element) {
        if(strcmp(element, "ALL" ) == 0) {
            if ((*BEG) == nullptr) { // if the list is empty nothing should be printed
                cout << endl;
                return;
            }

            Node* current = getNext(nullptr);
            while(current != nullptr) { // print all Nodes from list until the last element
                cout << current->value << " ";
                current = getNext(current);
            }
            cout << endl;
        }
        else cout << getIterator(getIteratorNr(element)).address->value << endl;
    }

    // adds new Node (value what) before the Node which is pointed by Iterator number to
    void addBefore(int to, unsigned long long int what) {
        if ((*BEG) == nullptr) { // if list is empty initialise a new BEG and END
            (*BEG) = new Node();
            (*BEG)->value = what;
            (*END) = *BEG;
        }
        else if(getIterator(to).address == (*BEG)) {
            Node *node = new Node();
            node->value = what;
            node->next = getIterator(to).address;
            getIterator(to).address->prev = node;
            (*BEG) = node;
        }
        else {
            Node *node = new Node();
            node->value = what;
            node->next = getIterator(to).address;
            getIterator(to).getPrevious().address->next = node;
            node->prev = getIterator(to).getPrevious().address;
            getIterator(to).address->prev = node;
        }
    }

    // adds new Node (value what) before the Node which is pointed by Iterator number to
    void addAfter(int to, unsigned long long int what) {
        if ((*BEG) == nullptr) { // if list is empty initialise a new BEG and END
            (*BEG) = new Node();
            (*BEG)->value = what;
            (*END) = *BEG;
        }
        else if(getIterator(to).address == (*END)) {
            Node* node = new Node();
            node->value = what;
            node->prev = getIterator(to).address;
            getIterator(to).address->next = node;
            (*END) = node;
        }
        else {
            Node* node = new Node();
            node->value = what;
            node->next = getIterator(to).getNext().address;
            getIterator(to).address->next = node;
            node->prev = getIterator(to).address;
            node->next->prev = node;
        }
    }

    // remove the Node which is pointed by Iterator number element
    void remove(int element) {
        Node* toDelete = getIterator(element).address;
        if(toDelete == (*BEG)) {
            (*BEG) = toDelete->next;
            if((*BEG) == nullptr) (*END) = *BEG; // if it was only Node in the list
            else (*BEG)->prev = nullptr; // new first Node can't store pointer to previous Node (it does not exist)
            getIterator(element).address = (*BEG);
        }
        else {
            if(toDelete == (*END)) {
                getIterator(element).getPrevious().address->next = nullptr; // new last Node can't store pointer to next Node (it does not exist)
                (*END) = getIterator(element).getPrevious().address;
                getIterator(element).address = (*END);
            }
            else {
                getIterator(element).address = getIterator(element).getNext().address;
                getIterator(element).address->prev = getIterator(element).address->prev->prev;
                getIterator(element).getPrevious().address->next = getIterator(element).address;
            }
        }
        for(int i = 0; i<ITERATORS_NUMBER+2; i++) { // every Iterator that point to the Node that must be deleted now must point to the next Node
            if(i == element) continue; // the Iterator which pointed to Node that must be deleted was previous change to point to the next Node
            if(getIterator(i).address == toDelete) {
                if(toDelete == (*END) && toDelete == (*BEG))
                    getIterator(i) = nullptr;
                else if (getIterator(element).address == (*END) && toDelete->next != nullptr)
                    getIterator(i).address = toDelete->next;
                else if(getIterator(element).address == (*END) && getIterator(i).address->prev != nullptr)
                    getIterator(i).address = getIterator(i).address->prev;
                else
                    getIterator(i).address = toDelete->next;
            }
        }
        delete toDelete;
    }





    // returns pointer to next Node in the list
    // if functions receives nullptr, returns first Node in the list
    Node* getNext(Node* currentNode) {
        if (currentNode == nullptr) return (*BEG);
        return currentNode->next;
    }

    // cleans list from all Nodes
    void deleteAll() {
        if ((*BEG) != nullptr) {
            while (true) {
                if (BEG != nullptr && (*BEG)->next == nullptr) break;
                remove((*BEG));
            }
            remove((*BEG));
        }
    }

private:
    // BEG stores pointer to first Node in the list, END to last
    Node** BEG = &allIterators[ITERATORS_NUMBER].address;
    Node** END = &allIterators[ITERATORS_NUMBER + 1].address;
    Iterator allIterators[ITERATORS_NUMBER+2]; // table that stores all Iterators included Iterators to first and last Node in the list

    // returns an Iterator of given number
    Iterator& getIterator(int number) {
        if (number >= 0 && number < ITERATORS_NUMBER + 2)
            return allIterators[number];
        throw;
    }

    // remove the selected Node -> this is function that ONLY works to delete all Nodes
    void remove(Node* node) {
        if(node == (*BEG)) { // if first Node of the list is removed -> change the BEG
            (*BEG) = node->next;
            if((*BEG) == nullptr) (*END) = *BEG; // if the list is empty, BEG and END should store nothing
            else (*BEG)->prev = nullptr;
        }
        else {
            node->prev->next = node->next;
            if (node == (*END)) (*END) = node->prev;
            else node->next->prev = node->prev;
        }
        delete node;
    }
};


#endif //CACHELIST_LIST_H