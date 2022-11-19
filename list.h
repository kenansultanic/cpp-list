#ifndef LIST_H
#define LIST_H
#include <initializer_list>
#include <bits/stdc++.h>

template <typename Type>
class List
{
    struct Node
    {
        Type element;
        Node *prev, *next;
        Node(Type element = Type(), Node *prev = nullptr, Node *next = nullptr):
                element(element), prev(prev), next(next) {}
    };
    Node *head;
    Node *tail;
    int size;
    void init();
    Node* split(Node*);
    Node* merge_sort(Node*);
    Node* merge(Node*, Node*);
public:

    class const_iterator
    {
    protected:
        Node *node;
    public:
        const_iterator(Node *node = nullptr): node(node) {}
        Type operator*() { return node -> element; }
        const_iterator operator++() { node = node -> next; return *this; }
        const_iterator operator++(int) { const_iterator it(*this); node = node -> next; return it; }
        const_iterator operator--() { node = node -> prev; return *this; }
        const_iterator operator--(int) { const_iterator it(*this); node = node -> prev; return it; }
        friend bool operator==(const_iterator it_1, const_iterator it_2) { return it_1.node == it_2.node; }
        friend bool operator!=(const_iterator it_1, const_iterator it_2) { return it_1.node != it_2.node; }
        friend class List<Type>;
    };

    class iterator: public const_iterator
    {
    public:
        iterator(Node *node = nullptr): const_iterator(node) {}
        Type& operator*() { return this -> node -> element; }
        iterator operator++() { this -> node = this -> node -> next; return *this; }
        iterator operator++(int) { iterator it(*this); this -> node = this -> node -> next; return it; }
        iterator operator--() { this -> node = this -> node -> prev; return *this; }
        iterator operator--(int) { iterator it(*this); this -> node = this -> node -> prev; return it; }
        friend bool operator==(iterator it_1, iterator it_2) { return it_1.node == it_2.node; }
        friend bool operator!=(iterator it_1, iterator it_2) { return it_1.node != it_2.node; }
        friend class List<Type>;
    };

    class const_reverse_iterator
    {
    protected:
        Node *node;
    public:
        const_reverse_iterator(Node *node = nullptr): node(node) {}
        Type operator*() { return node -> element; }
        const_reverse_iterator operator++() { node = node -> prev; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator it(*this); node = node -> prev; return it; }
        const_reverse_iterator operator--() { node = node -> next; return *this; }
        const_reverse_iterator operator--(int) {const_reverse_iterator it(*this); node = node -> next; return it; }
        friend bool operator==(const_reverse_iterator it_1, const_reverse_iterator it_2) { return it_1.node == it_2.node; }
        friend bool operator!=(const_reverse_iterator it_1, const_reverse_iterator it_2) { return it_1.node != it_2.node; }
        friend class List<Type>;
    } ;

    class reverse_iterator: public const_reverse_iterator
    {
    public:
        reverse_iterator(Node *node = nullptr): const_reverse_iterator(node) {}
        Type& operator*() { return this -> node -> element; }
        reverse_iterator operator++() { this -> node = this -> node -> prev; return *this; }
        reverse_iterator operator++(int) { reverse_iterator it(*this); this -> node = this -> node -> prev; return it; }
        reverse_iterator operator--() { this -> node = this -> node -> next; return *this; }
        reverse_iterator operator--(int) { reverse_iterator it(*this); this -> node = this -> node -> next; return it; }
        friend bool operator==(reverse_iterator it_1, reverse_iterator it_2) { return it_1.node == it_2.node; }
        friend bool operator!=(reverse_iterator it_1, reverse_iterator it_2) { return it_1.node != it_2.node; }
        friend class List<Type>;
    };

    List();
    List(int, Type = Type());
    List(const List&);
    List(List&&) noexcept;
    List(std::initializer_list<Type>);
    List(const_iterator, const_iterator);
    List(const_reverse_iterator, const_reverse_iterator);
    ~List(){ clear(); delete head; delete tail; }
    List& operator=(const List&);
    List& operator=(List&&) noexcept;
    iterator insert(iterator, Type);
    void push_back(Type value) { insert(tail, value); }
    void push_front(Type value) { insert(head -> next, value); }
    iterator erase(iterator);
    bool empty() const { return size == 0; }
    bool contains(Type el) const { for(auto it = begin(); it != end(); it++) if(*it == el) return true; return false; }
    int list_size() const { return size; }
    Type front() const { return head -> next -> element; }
    Type back() const { return tail -> prev -> element; }
    void pop_back() { erase(tail -> prev); }
    void pop_front() { erase(head -> next); }
    void clear() { while(!empty()) pop_back(); }
    void reverse();
    void unique();
    void rotate(int);
    void insert(iterator, List&);
    void insert(iterator, List&&);
    void remove(Type);
    void remove_if(std::function<bool(Type)>);
    void move(List&&);
    void sort();
    iterator begin() { return head -> next; }
    iterator end() { return tail; }
    reverse_iterator rbegin() { return tail -> prev; }
    reverse_iterator rend() { return head; }
    const_iterator begin() const { return head -> next; }
    const_iterator end() const { return tail; }
    const_reverse_iterator rbegin() const { return tail -> prev; }
    const_reverse_iterator rend() const { return head; }
    friend List operator+(const List&, const List&);
    void operator+=(const List&);
    void operator+=(List&&);
    static List merge(const List&, const List&);
    static void swap(List&, List&);
    Type operator[](int) const;
    Type& operator[](int);
};

#include "list.cpp"
#endif
