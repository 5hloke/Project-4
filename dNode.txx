#include "dNode.hpp"
#include <iostream>
template<class T>

dNode<T>::dNode()
{
    next = nullptr;
    prev = nullptr;
    item = NULL;

}

template<class T>
dNode<T> ::dNode(const T& anItem)
{
    item = anItem;
    prev = nullptr;
    next = nullptr;


}

template<class T>
dNode<T>::dNode(const T& anItem, dNode<T>* nextNodePtr, dNode<T>* prevNodePtr)
{
    item = anItem;
    next = nextNodePtr;
    prev = prevNodePtr;
}

template<class T>

void dNode<T>::setItem(const T& anItem)
{
    item = anItem;
}

template<class T>

void dNode<T>::setNext(dNode<T>* nextNodePtr)
{
    next = nextNodePtr;

}

template<class T>
void dNode<T>::setPrev(dNode<T>* prevNodePtr)
{
    prev = prevNodePtr;
}

template<class T>
T dNode<T>::getItem() const
{
    return item;
}

template<class T>
dNode<T>* dNode<T>::getNext() const
{
    return next;
}

template<class T>
dNode<T>* dNode<T>::getPrev() const
{
    return prev;
}

template<class T>
void dNode<T>::printNode() const
{
    std::cout << "Current Node: " << item << std::endl;

    if (next != nullptr)
    {
        std::cout << "Next Node: " << next->getItem() << std::endl;
    }
    else
    {
        std::cout << "Next Node: NULL " << std::endl;
    }

    if (prev != nullptr)
    {
        std::cout << "Next Node: " << prev->getItem() << std::endl;
    }
    else
    {
        std::cout << "Next Node: NULL " << std::endl;
    }
}
