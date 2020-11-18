#include <iostream>
#include "ListNode.h"
using namespace std;
template <class T>
//doubly linked list
class DoublyLinkedList {
    private:
    public:
        int size;
        ListNode<T> *front;
        ListNode<T> *back;
        DoublyLinkedList();
        ~DoublyLinkedList();
        void insertBack(T data);
        T removeFront();
        T getFront();
        void printList();
        int removed(int node);
        bool isEmpty();
        int getSize();
};
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size = 0;
    front = NULL;
    back = NULL;
}
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
}
template <class T>
void DoublyLinkedList<T>::insertBack(T d) {
    ListNode<T> *node = new ListNode<T>(d);
    if(size == 0) {
        front = node;
    }
    else {
        back->next = node;
        node->prev = back;
    }
    back = node;
    ++size;
}
//removes front node
template <class T>
T DoublyLinkedList<T>::removeFront() {
    if(!isEmpty()) {
        ListNode<T> *node = front;
        if(front->next == NULL) {
            front = NULL;
            back = NULL;
        }
        else {
            front->next->prev = NULL;
            front = front->next;
        }
        T temp = node->data;
        delete node;
        --size;
        return temp;
    }
    else {
        return T();
    }
}
//returns front node
template <class T>
T DoublyLinkedList<T>::getFront() {
    return front->data;
}
//prints nodes
template <class T>
void DoublyLinkedList<T>::printList() {
    ListNode<T> *curr = front;
    while(true) {
        if(curr->next == NULL) {
            break;
        }
        curr = curr->next;
    }
}
//returns removed
template <class T>
void DoublyLinkedList<T>::removed(int node) {
    int i = 0;
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;
    while(i != node) {
        prev = curr;
        curr = curr->next;
        ++i;
    }
    prev->next = curr->next;
    curr->next->prev = prev;
    curr->next = NULL;
    curr->prev = NULL;
    curr->data = NULL;
    --size;
    delete curr;
}
//checks if list is empty
template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return(size == 0);
}
template <class T>
//returns size of list
int DoublyLinkedList<T>::getSize() {
    return size;
}
