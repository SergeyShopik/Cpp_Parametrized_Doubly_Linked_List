#pragma once
#include<iostream>
#include<string>
using std::string;

// to do: reload '->' for iterator for <erase(size_t)> function

template<class T>
class DualList
{
public:
    class Node
    {
    public:
        T data;
        Node* prev;
        Node* next;

        Node() = default;
        Node(const T& _data, Node* _prev = nullptr, Node* _next = nullptr)
            : data(_data), prev(_prev), next(_next) {};
        ~Node() = default;
    };

    DualList() : size(0), head(nullptr), tail(nullptr) {};
    DualList(const DualList<T>&);
    ~DualList();

    void pushBack(const T&);
    void pushFront(const T&);
    void insert(const T&, size_t);
    void insert(const T&, size_t, size_t numOfElements);

    T popBack();
    T popFront();
    T erase(size_t);

    void replace(const T&, const T&);

    T& operator[](size_t);
    const T& operator[](size_t) const;

    template<class T>
    friend std::ostream& operator<<(std::ostream&, DualList<T>&);

private:
    size_t size;
    Node* head;
    Node* tail;

public:
    class Iterator
    {
    public:
        Iterator() = default;
        Iterator(Node* _ptr) : ptr(_ptr) {};
        ~Iterator() = default;

        // prefix form
        Iterator& operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        // postfix form
        Iterator& operator++(int)
        {
            Iterator temp(*this);// connect temp pointer with current object
            operator++();// increment for current object
            return temp;// return transformed object
        }
        // to do
        /*Iterator& operator--()
        Iterator& operator--(int)*/
        Iterator& operator+(int num)
        {
            // add error check
            while (--num)
                this->operator++();

            return *this;
        }

        // dereference operator
        T& operator*() const { return ptr->data; }
        Node* operator->();

        bool operator==(const Iterator& i) const
        {
            return ptr == i.ptr;
        }
        bool operator!=(const Iterator& i) const
        {
            return ptr != i.ptr;
        }

    private:
        Node* ptr;
    };

    // to do
    /*class Reverse_iterator
    {

    };*/
    //Reverse_iterator Rbegin() { return Reverse_iterator(tail); }
    //Reverse_iterator Rend() { return Reverse_iterator(head->prev); }

    void erase(Iterator start, Iterator end);
    T find(const T&);

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(tail->next); }

};

template <class T>
void DualList<T>::pushBack(const T& val)
{
    Node* temp = new Node(val, tail);
    if (size == 0)
    {
        head = temp;
    }
    else
    {
        tail->next = temp;
    }
    tail = temp;
    size++;
}

template<class T>
T DualList<T>::popBack()
{
    Node* temp = tail;
    T returnValue;
    if (size == 0)
    {
        std::cout << "List is empty.\n";
        return T();
    }
    if (size == 1)
        tail = head = nullptr;

    else
    {
        tail = temp->prev;
        tail->next = nullptr;
    }

    returnValue = temp->data;
    size--;
    delete temp;

    return returnValue;
}

template<class T>
T DualList<T>::popFront()
{
    Node* temp = head;
    T returnValue;
    if (size == 0)
    {
        std::cout << "List is empty.\n";
        return T();
    }
    if (size == 1)
        tail = head = nullptr;

    else
    {
        head = temp->next;
        head->prev = nullptr;
    }

    returnValue = temp->data;
    size--;
    delete temp;

    return returnValue;
}

template<class T>
std::ostream& operator<<(std::ostream& out, DualList<T>& list)
{
    if (list.size == 0)
    {
        out << "List is empty.\n";
        return out;
    }

    for (auto i = list.begin(); i != list.end(); i++)
        out << *i << " ";

    return out;
}
template<class T>
T& DualList<T>::operator[](size_t index)
{
    if (index >= size)
    {
        std::cout << "Wrong index.\n";
        exit(0);
    }
    Node* cur = head;
    for (size_t i = 0; i < index; i++, cur = cur->next);

    return cur->data;
}
template<class T>

const T& DualList<T>::operator[](size_t index) const
{
    if (index > size)
    {
        std::cout << "Wrong index.\n";
        return T();
    }
    Node* cur = head;
    for (size_t i = 0; i < index; i++, cur = cur->next);

    return cur->data;
}

template<class T>
DualList<T>::~DualList()
{
    while (size != 0)
    {
        popBack();
    }
}

template<class T>
T DualList<T>::erase(size_t pos)
{
    T returnValue;
    Node* cur = head;
    if (pos > size)
    {
        std::cout << "Position is out of range.\n";
        return T();
    }

    for (size_t i = 0; i < pos; i++, cur = cur->next);
    if (pos == 0) return popFront();
    if (pos == size) return popBack();
    returnValue = cur->data;

    // to do: reload '->' for iterator
    (cur->prev)->next = cur->next;
    (cur->next)->prev = cur->prev;
    delete cur;
    size--;

    return returnValue;


}

template<class T>
void DualList<T>::erase(Iterator start, Iterator end)
{
    if (start == nullptr)
    {
        std::cout << "Wrong range.\n";
        return;
    }
    size_t position = 0;
    while ((*this)[position++] != *start);

    size_t count = 0;

    Iterator cur = start;
    //for (; cur != end || cur != nullptr; count++, cur++);
    while ((*this)[count++] != *end);

    for (size_t i = 0; i <= count - position; i++)
        erase(position);
}

template<class T>
T DualList<T>::find(const T& val)
{
    Node* cur = head;
    while (cur->data != val && cur != tail->next)
        cur = cur->next;

    if (cur == nullptr)
        return T();
    
    return cur->data;
}
