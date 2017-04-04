//
// Created by Alex Vovkotrub on 31.03.17.
//

#pragma once

#include <iterator>
#include <assert.h>

template <class type>
class List {
    struct Node {
        type value;
        Node * next, * prev;

        Node(type value, List::Node *next, List::Node *prev) : value(value), next(next), prev(prev) {}
    };
    
    Node* root;
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
        self_type operator--() { pointer tmp =ptr_->prev;
            return tmp; }
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
        self_type operator++() { pointer tmp = ptr_ = ptr_->next;
            return tmp; }
        self_type operator--() { pointer tmp =ptr_->prev;
            return tmp; }
        reference operator*() { return *ptr_; }
        const type operator->() { return ptr_->value; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        Node *getPtr_() { return ptr_; }
    private:
        pointer ptr_;
    };

    List() : root(nullptr), size(0) {}

    List(int count){
        root = (Node*) malloc(count * sizeof(Node));
        Node* tmp1 = root, * tmp2;
        root->prev= nullptr;
        for (int i = 0; i < count ; ++i) {
            tmp2 = tmp1++;
            tmp1->prev = tmp2;
            tmp2->next = tmp1;
        }
        tmp1->next = nullptr;
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
        Node* ptr1 = root, *ptr2;
        while (ptr1->next != nullptr) {
            ptr2 = ptr1;
            ptr1++;
            delete ptr2;
        }
    }

    void insert(iterator after, type value){
        if (after == this->end()){
            root = new Node(value, nullptr, nullptr);
            return;
        }
        iterator before = after;
        ++before;
        (*before).prev = new Node(value, before.getPtr_(), after.getPtr_());
        (*after).next = (*before).prev;
        size += 1;
    }

};

