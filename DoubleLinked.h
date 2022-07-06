#ifndef DOUBLELINKED_h
#define DOUBLELINKED_h
#include <iostream>
#include "Exception.h"
#include "Part.h"
using namespace std;

template <class H>
class DoubleLinked {
private:
    struct Node {
        H* data = nullptr;
        struct Node* next = nullptr;
        struct Node* prev = nullptr;
    };
    Node* head = nullptr;
    int size;
    int searchPos = 0; //for SeeAt
public:
    DoubleLinked();
    ~DoubleLinked();
    void AddItem(H*);
    H* GetItem(H*);
    bool IsInList(H*);
    bool IsEmpty();
    int Size();
    H* SeeNext();
    H* SeePrev();
    H* SeeAt(int);
    void Reset();
    void DisplayList();

    bool operator == (const Part&);
    bool operator < (const Part&);
    bool operator > (const Part&);
};

template<class H>
DoubleLinked<H>::DoubleLinked() {
    int size = 0;
    head = nullptr;
}

template<class H>
DoubleLinked<H>::~DoubleLinked() {
    Node* nn = new Node;
    Node* np;

    nn = head;

    while (nn != nullptr) {
        np = nn->next;
        delete nn;
        nn = np;
    }
}

template<class H>
void DoubleLinked<H>::AddItem(H* item) {
    Node* nn = new Node;
    Node* np;

    nn->data = item;

    if (!head) {
        head = nn;
    }
    else {
        if (*item < *head->data) {
            nn->next = head;
            head->prev = nn;
            head = nn;
            size++;
            return;
        }
        np = head;
        while (np->next != NULL && *np->next->data < *item) {
            np = np->next;
        }
        nn->next = np->next;
        np->next = nn;
        nn->prev = np;
        if (size >= 3 && nn->next != nullptr) {
            np = nn->next;
            np->prev = nn;
        }
    }
    size++;
}

template<class H>
H* DoubleLinked<H>::GetItem(H* item) {
    if (IsEmpty()) {
        return nullptr;
    }
    Node* np = head;
    if (*head->data == *item) {
        Node* oh = head;// node of old head
        H* retval = head->data;// return val set to val being removed
        head = head->next;//head is set to the next node in the list
        delete oh;//delete old head to prevent memory leak
        size--;
        return retval;
    }
    while (np->next != NULL && np->next->data != item) {
        np = np->next;
    }
    if (np->next == nullptr) {//if end is reached and item not found, return nullptr
        //cout << "--Item not found--" << endl;
        return nullptr;
    }
    Node* dp = np->next;//sets a delete pointer to the next spot from where np stops
    np->next = dp->next;//assigns the pointer(currently pointing to next) to the next next value(just skips the value being removed)
    if (dp->next != nullptr) {
        np = dp->next;
        np->prev = dp->prev;
    }
    else {
        np->next = nullptr;
    }
    H* retval = dp->data; //assigns the value 
    delete dp;
    size--;
    return retval;
}

template<class H>
bool DoubleLinked<H>::IsInList(H* item) {
    Node* np = head;
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (head->data == item) {
        return true;
    }
    while (np->next != NULL && np->next->data != item) {
        np = np->next;
    }
    if (np->next == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

template<class H>
bool DoubleLinked<H>::IsEmpty() {
    return size == 0;
}

template<class H>
int DoubleLinked<H>::Size() {
    return size;
}

template<class H>
H* DoubleLinked<H>::SeeNext() {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos >= size - 1 || searchPos < 0) {
        throw Exception("Index out of bounds");
    }
    Node* np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != searchPos + 1) {
        np = np->next;
        posCount++;
    }
    searchPos++;
    return np->data;
}

template<class H>
H* DoubleLinked<H>::SeePrev() {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos > size || searchPos <= 0) {
        throw Exception("Index out of bounds");
    }
    Node* np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != searchPos - 1) {
        np = np->next;
        posCount++;
    }
    searchPos--;
    return np->data;
}

template<class H>
H* DoubleLinked<H>::SeeAt(int pos) {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos > size || searchPos < 0) {
        throw Exception("Index out of bounds");
    }
    Node* np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != pos) {
        np = np->next;
        posCount++;
    }
    searchPos = posCount;
    return np->data;
}

template<class H>
void DoubleLinked<H>::Reset() {
    searchPos = 0;
}

template<class H>
void DoubleLinked<H>::DisplayList() {
    int posCount = 0;
    Node* np = head;
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (head->next == NULL) {
        np->data->Display();
    }
    else {
        while (np->next != NULL && posCount <= size) {
            np->data->Display();
            cout << "\n   /\\ \n";
            cout << "\n   ||  \n";
            cout << "\n   ||  \n";
            cout << "\n   ||  \n";
            cout << "\n   \\/  \n";
            np = np->next;
            posCount++;
        }
        np->data->Display();
    }
    cout << endl;
}

template<class H>
bool DoubleLinked<H>::operator == (const Part& item) {
    return item.getSKU() == this->item.getSKU();
}

template<class H>
bool DoubleLinked<H>::operator < (const Part& item) {
    return item.getSKU() < this->item.getSKU();
}

template<class H>
bool DoubleLinked<H>::operator > (const Part& item) {
    return item.getSKU() > this->item.getSKU();
}

#endif
