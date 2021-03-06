// sorted chain, implements dictionary

#ifndef __SORTEDCHAIN__
#define __SORTEDCHAIN__

#include <iostream>

#include "pairnode.h"
using namespace std;

template <class K, class E>
class sortedChain {
   public:
    sortedChain() {
        firstNode = NULL;
        dSize = 0;
    }
    ~sortedChain();

    bool empty() { return dSize == 0; }
    int size() { return dSize; }
    pair<K, E> *find(K &);
    void erase(K &);
    void insert(pair<K, E> &);
    void output(ostream &out);

   protected:
    pairNode<K, E> *firstNode;  // pointer to first node in chain
    int dSize;                  // number of elements in dictionary
};

template <class K, class E>
sortedChain<K, E>::~sortedChain() {  // Destructor.  Delete all nodes.
    while (firstNode != NULL) {      // delete firstNode
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class K, class E>
pair<K, E> *sortedChain<K, E>::find(
    K &theKey) {  // Return pointer to matching pair.
    // Return NULL if no matching pair.
    pairNode<K, E> *currentNode = firstNode;

    // search for match with theKey
    while (currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;

    // verify match
    if (currentNode != NULL && currentNode->element.first == theKey)
        // yes, found match
        return &currentNode->element;

    // no match
    return NULL;
}

template <class K, class E>
void sortedChain<K, E>::insert(
    pair<K, E>
        &thePair) {  // Insert thePair into the dictionary. Overwrite existing
    // pair, if any, with same key.
    pairNode<K, E> *p = firstNode,
                   *tp = NULL;  // tp trails p

    // move tp so that thePair can be inserted after tp
    while (p != NULL && p->element.first < thePair.first) {
        tp = p;
        p = p->next;
    }

    // check if there is a matching pair
    if (p != NULL && p->element.first == thePair.first) {  // replace old value
        p->element.second = thePair.second;
        return;
    }

    // no match, set up node for thePair
    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

    // insert newNode just after tp
    if (tp == NULL)
        firstNode = newNode;
    else
        tp->next = newNode;

    dSize++;
    return;
}

template <class K, class E>
void sortedChain<K, E>::erase(
    K &theKey) {  // Delete the pair, if any, whose key equals theKey.
    pairNode<K, E> *p = firstNode,
                   *tp = NULL;  // tp trails p

    // search for match with theKey
    while (p != NULL && p->element.first < theKey) {
        tp = p;
        p = p->next;
    }

    // verify match
    if (p != NULL && p->element.first == theKey) {  // found a match
        // remove p from the chain
        if (tp == NULL)
            firstNode = p->next;  // p is first node
        else
            tp->next = p->next;

        delete p;
        dSize--;
    }
}

template <class K, class E>
void sortedChain<K, E>::output(
    ostream &out) {  // Insert the chain elements into the stream out.
    for (pairNode<K, E> *currentNode = firstNode; currentNode != NULL;
         currentNode = currentNode->next)
        out << currentNode->element.first << " " << currentNode->element.second
            << "  ";
}

// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, sortedChain<K, E> &x) {
    x.output(out);
    return out;
}

#endif
