#pragma once

#ifndef CHAINHASHTABLE_h
#define CHAINHASHTABLE_h
#include <iostream>
#include "Exception.h"
#include "Part.h"
#include "HashTable.h"
#include "DoubleLinked.h"
using namespace std;

template<class H>
class ChainHashTable : public HashTable<H> {
private:
    DoubleLinked<H>* values[250];
    int size = 250;
    int length = 0;
public:
    int chainCompCount = 0;
    ChainHashTable();
    ~ChainHashTable();
    void InsertItem(H*);
    H* GetItem(H* val);
    H* RemoveItem(H* val);
    int GetLength();
};

template<class H>
ChainHashTable<H>::ChainHashTable() {
    for (int i = 0; i < size; i++) {
        values[i] = new DoubleLinked<H>;
    }
}

template<class H>
ChainHashTable<H>::~ChainHashTable() {
    int i = 0;
    while (values[i] != nullptr && i < length) {
        values[i]->~DoubleLinked<H>();
        i++;
    }
}

template<class H>
void ChainHashTable<H>::InsertItem(H* item) {
    int spot = HashTable<H>::Hash(item->getSKU());
    values[spot]->AddItem(item);
    length++;
}

template<class H>
H* ChainHashTable<H>::GetItem(H* item) {
    int spot = HashTable<H>::Hash(item->getSKU());
    H* retval = values[spot]->SeeAt(spot);
    chainCompCount++;
    return retval;
}

template<class H>
H* ChainHashTable<H>::RemoveItem(H* item) {
    int spot = HashTable<H>::Hash(item->getSKU());
    length--;
    return values[spot]->GetItem(item);
}

template<class H>
int ChainHashTable<H>::GetLength() {
    return length;
}

#endif

