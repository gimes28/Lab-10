#pragma once
#ifndef HASHTABLE_h
#define HASHTABLE_h
#include <iostream>
#include "Exception.h"
#include "Part.h"
#include "DoubleLinked.h"
using namespace std;

template<class H>
class HashTable {
private:
protected:
    H* values[100];
    int length = 0;
    int size = 100;
    int Hash(string hashVal);
public:
    int compCount = 0;
    HashTable();
    ~HashTable();
    void InsertItem(H* val);
    H* RemoveItem(H* val);
    H* GetItem(H* val);
    int GetLength();
};

template<class H>
int HashTable<H>::Hash(string hashVal) {
    int sumASCII = 0;
    for (int i = 0; i < hashVal.size(); i++) {
        sumASCII += (int)hashVal[i];
    }
    return sumASCII % size;
}

template<class H>
HashTable<H>::HashTable() {// default 
    for (int i = 0; i < size; i++) {
        values[i] = nullptr;
    }
}

template<class H>
HashTable<H>::~HashTable() { //Destructor
    for (int i = 0; i < size; i++) {
        values[i] = nullptr;
    }
    length = 0;
}

template<class H>
void HashTable<H>::InsertItem(H* val) {
    if (length >= size) {
        throw(Exception("HashTable is full"));
    }
    int spot = Hash(val->getSKU());
    while (values[spot] != nullptr) {
        spot = (spot + 1) % size;
    }
    values[spot] = val;
    length++;
}

template<class H>
H* HashTable<H>::RemoveItem(H* val) {
    if (length <= 0) {
        throw(Exception("HashTable is empty"));
    }
    int spot = Hash(val->getSKU());
    H* retval = values[spot];
    if (retval == nullptr) {
        return retval;
    }
    values[spot] = nullptr;
    length--;
    return retval;
}

template<class H>
H* HashTable<H>::GetItem(H* val) {
    if (length <= 0) {
        throw(Exception("HashTable is empty"));
    }
    int spot = Hash(val->getSKU());
    while (values[spot] != nullptr && values[spot] != val) {
        compCount++;
        spot = (spot + 1) % size;
    }
    if (values[spot] == nullptr) {
        compCount++;
        return nullptr;
    }
    return values[spot];
}

template<class H>
int HashTable<H>::GetLength() {
    return length;
}

#endif