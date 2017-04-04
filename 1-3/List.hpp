//
// Created by Alex Vovkotrub on 31.03.17.
//

#pragma once

#include <iterator>
#include <assert.h>

//TODO: reverse iterator

template <class type>
class List {
    struct Node {
        type value;
        Node * next, * prev;

        Node(type value, List::Node *prev, List::Node *next) : value(value), next(next), prev(prev) {}
    };
    
    Node *root, *head;
    int size;
public:
    
    class iterator {
    public:
        typedef iterator self_type;
        typedef Node& reference;
        typedef Node* pointer;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef int difference_type;
        iterator(pointer ptr) : ptr_(ptr) {}
        self_type operator++() { pointer tmp = ptr_ = ptr_->next;
            return tmp; }
        self_type operator++(int){
            iterator tmp = *this;
            return ++tmp;
        }
        self_type operator--() { pointer tmp =ptr_->prev;
            return tmp; }
        self_type operator--(int){
            iterator tmp = *this;
            return --tmp;
        }
        reference operator*() { return *ptr_; }
        type operator->() { return ptr_->value; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        Node *getPtr_() { return ptr_; }
    private:
        pointer ptr_;
    };

    class const_iterator {
    public:
        typedef const_iterator self_type;
        typedef type value_type;
        typedef Node& reference;
        typedef Node* pointer;
        typedef int difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        const_iterator(pointer ptr) : ptr_(ptr) { }
        self_type operator++() { pointer tmp = ptr_ = ptr_->next;//prefix
            return tmp; }
        self_type operator++(int){                               //postfix
            const_iterator tmp = *this;
            return ++tmp;
        }
        self_type operator--() { pointer tmp =ptr_->prev;
            return tmp; }
        self_type operator--(int){
            const_iterator tmp = *this;
            return --tmp;
        }
        reference operator*() { return *ptr_; }
        const type operator->() { return ptr_->value; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        Node *getPtr_() { return ptr_; }
    private:
        pointer ptr_;
    };
    
    List() : root(nullptr), size(0) {}

    List(uint32_t count){
        root = new Node(0, nullptr, nullptr);
        Node *tmp1 = root, *tmp2;
        for (int i = 0; i < count - 1; ++i) {
            tmp2 = tmp1;
            tmp1 = new Node(0, tmp2, nullptr);
            tmp2->next = tmp1;
        }
        head = tmp1;
        size = count;
    }

    iterator begin()
    {
        return iterator(root);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator begin() const
    {
        return const_iterator(root);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }

    type operator[](iterator i){
        return (*i).value;
    }

    virtual ~List() {
        if (root == nullptr)
            return;
        Node* ptr1 = root, *ptr2;
        while (ptr1->next != nullptr) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            delete ptr2;
        }
    }
    
    
    
    bool empty(){ return !bool(size);}
    
    iterator insert(iterator after, type value){
        if (after == this->end()){
            root = new Node(value, nullptr, nullptr);
            head = root;
            size += 1;
            return iterator(root);
        }
        if (after.getPtr_()->next != nullptr) {
            iterator before = after;
            ++before;
            (*before).prev = new Node(value, before.getPtr_(), after.getPtr_());
            (*after).next = (*before).prev;
        } else {
            head->next = new Node(value, head, nullptr);
            head = head->next;
        }
        size += 1;
        return ++after;
    }
    
    iterator push_back(type value){
        return this->insert(iterator(head), value);
    }
    
    type pop_back(){
        assert((size > 0) && "List is empty, push back failed");
        if (size == 1) {
            type tmp = head->value;
            head = nullptr;
            delete root;
            root = nullptr;
            size = 0;
            return tmp;
        }
        type tmp = head->value;
        head = head->prev;
        delete head->next;
        head->next = nullptr;
        size -= 1;
        return tmp;
    }

};











