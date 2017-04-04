//
//  LinkedList.hpp
//  LinkedList
//
//  Created by Alex Vovkotrub on 17.02.17.
//  Copyright © 2017 Alex Vovkotrub. All rights reserved.
//

#pragma once

#include <vector>

using namespace std;

template <class T>
class Node {
    template<class B>
    friend class LinkedList;
    template<class A>
    friend class ListIterator;
private:
    T data;
    Node* next;
public:
    Node(){
        next = nullptr;
    }
    Node(T data, Node<T> * next = nullptr){
        this->next = next;
        this->data = data;
    }
    void operator=(T data){
        this->data = data;
    }
    T getData(){
        return data;
    }
    Node* getNext(){
        return next;
    }
};

template<class T>
struct ListIterator {
    T* ptr = nullptr, *root;
    uint32_t index = 0;
    ListIterator(){}
    void restart(){
        index = 0;
        ptr = root;
    }
    void moveNext(){
        index += 1;
        ptr = ptr->next;
    }
};

template <class T>
class LinkedList {
    Node<T> *head = nullptr;
public:
    uint32_t size = 0;
    ListIterator<Node<T>> iter;
    void createRoot(){
        iter.root = new Node<T>();
        iter.restart();
    }
    
    LinkedList(){
    }
    
    LinkedList(const uint32_t count){
        if (count == 0) {
            return;
        }
        createRoot();
        Node<T> *ptr = iter.root;
        size = 1;
        for (int i = 0; i < count - 1; i++) {
            ptr->next = new Node<T>();
            ptr = ptr->next;
            size += 1;
        }
        head = ptr;
    }
    
    LinkedList(const vector<T> dataArray){
        LinkedList();
        Node<T> *ptr = iter.root;
        for (int i = 0; i < dataArray.length(); i++) {
            ptr->next = new Node<T>(dataArray[i]);
            ptr = ptr->next;
            size += 1;
        }
        size = dataArray.length();
        head = ptr;
    }
    
    bool isEmpty(){
        if (size == 0) {
            return true;
        }
        return false;
    }
    
    Node<T>& operator[](int index){
        if (index > size) {
            out_of_range("out of range of the list");
        }
        if (index < iter.index) {
            iter.restart();
        }
        while(iter.index != index){
            iter.moveNext();
        }
        return *iter.ptr;
    }
    
    const Node<T>& operator[](int index) const{
        if (index > size) {
            out_of_range("out of range of the list");
        }
        if (index < iter.index) {
            iter.restart();
        }
        while(iter.index != index){
            iter.moveNext();
        }
        return *iter.ptr;
    }
    
    void pushBack(T data){
        if (iter.root == nullptr) {
            iter.root = head = new Node<T>(data);
        }else{
            head->next = new Node<T>(data);
            head = head->next;
        }
        size += 1;
    }
    
    void insert(int after, T data){
        if (after > size) {
            throw out_of_range("out of range of the list");
        }
        if(after == size ){
            pushBack(data);
            return;
        }
        Node<T> * left;
        if (after < iter.index) {
            iter.restart();
        }
        while (iter.index != after - 1) {
            iter.moveNext();
        }
        left = iter.ptr;
        iter.moveNext();
        left->next = new Node<T>(data, iter.ptr);
        size += 1;
    }
    
    void operator+=(const LinkedList b){
        size += b.size;
        head->next = b->root;
    }
    
    ~LinkedList(){
        Node<T> *ptr = iter.root, *prev;
        for (int k = 0; k < size; k++) {
            prev = ptr;
            ptr = ptr->next;
            delete prev;
        }
    }
    
    void erase(int at){
        if (at > size + 1) {
            throw out_of_range("out of range of the list");
        }
        Node<T> * left;
        iter.restart();
        if(size == 1){
            delete iter.root;
            iter.root = nullptr;
            head = nullptr;
        }else{
            while (iter.index != at - 1) {
                iter.moveNext();
            }
            left = iter.ptr;
            iter.moveNext();
            delete left->next;
            left->next = iter.ptr->next;
            if(head == iter.ptr)
                head = left;
            iter.moveNext();
        }
        size -= 1;
    }
    
    T pop(){
        T data = head->getData();
        erase(size-1);
        return data;
    }
    
};
