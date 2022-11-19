#ifndef LIST_CPP
#define LIST_CPP
#include "list.h"
#include <stdexcept>

template <typename Type>
void List<Type>::init()
{
    size = 0;
    head = new Node;
    tail = new Node(Type(), head);
    head -> next = tail;
}

template <typename Type>
List<Type>::List() { init(); }

template <typename Type>
List<Type>::List(int n, Type value)
{
    init();
    for(int i(0); i < n; i++)
        push_back(value);
}

template <typename Type>
List<Type>::List(const List<Type>& copy)
{
    init();
    for(auto it = copy.begin(); it != copy.end(); it++)
        push_back(*it);
}

template <typename Type>
List<Type>::List(List<Type>&& rhs) noexcept
{
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;
}

template <typename Type>
List<Type>::List(std::initializer_list<Type> l)
{
    init();
    for(auto it = l.begin(); it != l.end(); it++)
        push_back(*it);
}

template <typename Type>
List<Type>::List(const_iterator it1, const_iterator it2)
{
    init();
    while(it1 != it2)
        push_back(*(it1++));
}

template <typename Type>
List<Type>::List(const_reverse_iterator it1, const_reverse_iterator it2)
{
    init();
    while(it1 != it2)
        push_back(*(it1++));
}

template <typename Type>
List<Type>& List<Type>::operator=(const List<Type>& rhs)
{
    clear();
    for(auto it = rhs.begin(); it != rhs.end(); it++)
        push_back(*it);
    return *this;
}

template <typename Type>
List<Type>& List<Type>::operator=(List<Type>&& rhs) noexcept
{
    clear();
    delete head;
    delete tail;
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;
    return *this;
}

template <typename Type>
typename List<Type>::iterator List<Type>::insert(List<Type>::iterator it, Type vrijednost)
{
    Node *node = new Node(vrijednost, it.node -> prev, it.node);
    it.node -> prev = node;
    node -> prev -> next = node;
    size++;
    return node;
}

template <typename Type>
typename List<Type>::iterator List<Type>::erase(List<Type>::iterator it)
{
    iterator i(it.node -> next);
    it.node -> prev -> next = it.node -> next;
    it.node -> next -> prev = it.node -> prev;
    delete it.node;
    size--;
    return i;
}

template <typename Type>
List<Type> operator+(const List<Type> &l1, const List<Type> &l2)
{
    List<Type> i(l1);

    for(auto it = l2.begin(); it != l2.end(); it++)
        l1.push_back(*it);
    return i;
}

template <typename Type>
void List<Type>::operator+=(const List<Type>& l)
{
    for(auto it = l.begin(); it != l.end(); it++)
        push_back(*it);
}

template <typename Type>
void List<Type>::operator+=(List<Type>&& rhs)
{
    tail -> prev -> next = rhs.head -> next;
    rhs.head -> next -> prev = tail -> prev;
    tail = rhs.tail;
    size += rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;
}

template <typename Type>
void List<Type>::reverse()
{
    List<Type> copy(*this);
    clear();
    for(auto it = copy.rbegin(); it != copy.rend(); it++)
        push_back(*it);
}

template <typename Type>
void List<Type>::unique()
{
    List<Type> copy(*this);
    clear();

    auto it = copy.begin();
    while(it != copy.end())
    {
        Type element = *it++;
        push_back(element);
        while(element == *it)
            it++;
    }
}

template <typename Type>
List<Type> List<Type>::merge(const List<Type>& l1, const List<Type>& l2)
{
    List<Type> list;
    auto it_1 = l1.begin();
    auto it_2 = l2.begin();
    while(it_1 != l1.end())
    {
        if(*it_1 <= *it_2)
            list.push_back(*it_1);

        while(*it_1 >= *it_2 && it_2 != l2.end())
        {
            list.push_back(*it_2);
            it_2++;
        }
        it_1++;
    }
    while(it_2 != l2.end())
        list.push_back(*(it_2++));
    return list;
}

template <typename Type>
void List<Type>::swap(List<Type>& l1, List<Type>& l2)
{
    typename List<Type>::Node *temp_head = l1.head;
    typename List<Type>::Node *temp_tail = l1.tail;
    int size = l1.size;

    l1.head = l2.head;
    l1.tail = l2.tail;
    l1.size = l2.size;

    l2.head = temp_head;
    l2.tail = temp_tail;
    l2.size = size;
}

template <typename Type>
Type List<Type>::operator[](int index) const
{
    if (index < 0)
        throw std::invalid_argument("indeks smaller than zero");
    if (index >= size)
        throw std::invalid_argument("indeks greater than list size");
    if(index < size - index)
    {
        auto it = begin();
        for(int i = 0; i < index; i++)
            it++;
        return *it;
    }
    else
    {
        auto it = rbegin();
        for(int i = 0; i < size - index - 1; i++)
            it++;
        return *it;
    }
}

template <typename Type>
Type& List<Type>::operator[](int index)
{
    if (index < 0)
        throw std::invalid_argument("index smaller than zero");
    if (index >= size)
        throw std::invalid_argument("index greater than list size");
    if(index < size - index)
    {
        auto it = begin();
        for(int i = 0; i < index; i++)
            it++;
        return *it;
    }
    else
    {
        auto it = rbegin();
        for(int i = 0; i < size - index - 1; i++)
            it++;
        return *it;
    }
}

template <typename Type>
void List<Type>::rotate(int k)
{
    for(int i = 0; i < k; i++)
    {
        Type element = *(--end());
        pop_back();
        push_front(element);
    }
}

template <typename Type>
void List<Type>::insert(List<Type>::iterator i, List<Type>& list)
{
    auto it = list.rbegin();
    while(it != list.rend())
        insert(i, *(it++));
}

template <typename Type>
void List<Type>::insert(List<Type>::iterator i, List<Type>&& list)
{
    i.node -> next -> prev = list.tail -> prev;
    list.tail -> prev -> next = i.node -> next;
    list.head -> next -> prev = i.node;
    i.node -> next = list.head -> next;
    size += list.list_size();
    list.head = list.tail = nullptr;
    list.size = 0;
}

template <typename Type>
void List<Type>::remove(Type element)
{
    for(auto it = begin(); it != end(); it++)
        if (*it == element)
            erase(it);
}

template <typename Type>
void List<Type>::remove_if(std::function<bool(Type)> f)
{
    for(auto it = begin(); it != end(); it++)
        if(f(*it))
            erase(it);
}

template <typename Type>
void List<Type>::move(List<Type>&& rhs)
{
    clear();
    delete head;
    delete tail;
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;
}

template <typename Type>
void List<Type>::sort()
{
    tail -> prev -> next = nullptr;
    head -> next = merge_sort(head->next);

    Node *node = head -> next;
    while(node -> next != nullptr)
        node = node -> next;
    node -> next = tail;
    node -> next -> prev = node;
    head -> next -> prev = head;
}

template <typename Type>
typename List<Type>::Node* List<Type>::split(List<Type>::Node *head)
{
    Node *fast = head, *slow = head;
    while (fast -> next && fast -> next -> next)
    {
        fast = fast -> next -> next;
        slow = slow -> next;
    }
    Node *temp = slow -> next;
    slow -> next = nullptr;
    return temp;
}

template <typename Type>
typename List<Type>::Node* List<Type>::merge_sort(List<Type>::Node *head)
{
    if (!head || !head -> next)
        return head;
    Node *second = split(head);

    head = merge_sort(head);
    second = merge_sort(second);

    return merge(head, second);
}

template <typename Type>
typename List<Type>::Node* List<Type>::merge(List<Type>::Node *first, List<Type>::Node *second)
{
    if (!first)
        return second;

    if (!second)
        return first;

    if (first -> element < second -> element) {
        first -> next = merge(first -> next, second);
        first -> next -> prev = first;
        first -> prev = nullptr;
        return first;
    }
    else
    {
        second -> next = merge(first, second -> next);
        second -> next -> prev = second;
        second -> prev = nullptr;
        return second;
    }
}

#endif