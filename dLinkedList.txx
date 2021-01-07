#include "dLinkedList.hpp"
#include "dNode.hpp"
#include <iostream>



template<class T>
// works 
// Implemementation of the default constructor 
dLinkedList<T>::dLinkedList()
{
    itemCount = 0; // size of the list is equal to 0 
    headPtr = nullptr; // Head Pointer = nullpointer
    tailPtr = nullptr; // tail Pointer = nullpointer
}

//works 
template<class T>
// Implementation of the Parameterized constructor
dLinkedList<T>::dLinkedList(const dLinkedList<T>& alist)
{
    itemCount = alist.getCurrentSize();
    dNode<T>* aphd = alist.getHead(); // Pointer storing the value of the head pointer of the list that is to be copied
    dNode<T>* apt = alist.getTail(); // Pointer storing the value of the tail pointer of the list that is to be copied
    if (aphd == nullptr) { // If the List to be copied is empty
        headPtr = nullptr; // then both headpointer and the tailpointer are set to nullptr
        tailPtr = nullptr;
    }
    else {
        headPtr = new dNode<T>(); // creating a new node fr the head Pointer
        tailPtr = headPtr; // if there is only ine node then head pointer = tail pointer
        headPtr->setItem(aphd->getItem()); // setting he item in the first node
        headPtr->setPrev(nullptr); // Setting the previos pointer to a nullpoiner
        dNode<T>* newchainptr = headPtr; // Creadting a new pointer to dNode<T> to store the value of headpointer and traverse through teh list
        aphd = aphd->getNext(); // Get the next node in the list to be copied and store it in aphd
        while (aphd != nullptr) { // If it is not the end of the list 

            T nextitem = aphd->getItem(); // get the item in the current node

            dNode<T>* newNodeptr = new dNode<T>(nextitem); // create a new node in the copy list and set the item
            newNodeptr->setPrev(newchainptr); // set previous pointer of new node pointer to newchainpointer
            newchainptr->setNext(newNodeptr); // newchain pointer set Next node to newNode pointer

            newchainptr = newchainptr->getNext(); // Store the next value of newchainpointer and store it in newchainpoi    nter
            aphd = aphd->getNext(); // Move to the next node in the alist 
        }
        tailPtr = newchainptr;  // Setting the address of the last node equal to the tail Ptr
        newchainptr->setNext(nullptr);

    }

}

// Destructor deallocates all he memory
template<class T>
// Implementation of the Destructor
dLinkedList<T>:: ~dLinkedList()
{
    clear(); //Clears the list and frees the memory 
}

// works
template<class T>
// Implementation of getCurrentSize()
int dLinkedList<T>::getCurrentSize() const
{
    return itemCount; // returns the size of the list
}

//works 
template<class T>
// Implementation of the isEmpty() method
bool dLinkedList<T>::isEmpty() const
{
    bool flag = false;
    if (itemCount == 0) { // Checks if the size of the list is zero i.e no itme in the list
        flag = true; // setting the flag to true
    }
    else {
        flag = false;
    }
    //returning if the list is empty(true) or not(false)
    return flag;
}

// to add a new nod ein the beginning of the list 
template<class T>
bool dLinkedList<T>::add(const T& newEntry) {

    //Creating a new node 
    dNode<T>* newnodeptr = new dNode<T>();
    newnodeptr->setItem(newEntry); // Setting the entry in thr new node to the given entry 
    newnodeptr->setNext(headPtr); // The next pointer = head pointer
    newnodeptr->setPrev(nullptr); // Previous pointer = bullptr

    if (headPtr != nullptr) { // If it is not the first element in the list 

        headPtr->setPrev(newnodeptr); // Current headpointers previous pointer is the new node 

    }
    else {

        tailPtr = newnodeptr; // If it is the first element in the list then newpointer is also the tailpointer
        tailPtr->setNext(nullptr); // Next pointer = nullptr

    }

    headPtr = newnodeptr; // Lastly headPtr = newNodeptr
    itemCount++; // increase the item Count by 1
    return true; // return true 
}

// Finding an element in the list and removing the element in the list 
//The methode find the entry to be removed and replaces it with the value in the first node and 
// Deletes the first node 
template<class T>
bool dLinkedList<T>::remove(const T& anEntry) {

    dNode<T>* target_entry = getPointerTo(anEntry); // getPointerTo returns the pointer to the node that has the entry to be removed
    bool canremove = false; //This is a flag set to false to begin with 
    if (!isEmpty() && target_entry != nullptr) { // if the list is not empty  and the target_entry is not a nullptr
        canremove = true; // Item is found and can be removed from the list 
    }
    else {
        canremove = false; // Else the item to be removed can not be found and can not be removed
    }

    if (canremove && itemCount != 1) { // canremove is true and the itemcount is not 1
        target_entry->setItem(headPtr->getItem()); // set the item value of the node to the value in the headPtr
        dNode<T>* nodetodeleteptr = headPtr; // nodetobedeleted  is headptr

        headPtr = headPtr->getNext(); //head Ptr is set to the next pointer 
        headPtr->setPrev(nullptr); // setting previous pointer of the current head pointer to nullptr

        nodetodeleteptr->setNext(nullptr); // Clearing the memory 
        delete nodetodeleteptr; // delete the node
        nodetodeleteptr = nullptr; // set it equal to nullptr
        itemCount--; // Decrease the size by one 
    }
    else if (canremove && itemCount == 1) {
        headPtr = nullptr; // Clears the list if there s only one element in the list
        tailPtr = headPtr;
        delete target_entry;
        target_entry = nullptr;
        itemCount--;
    }

    return canremove; // return canremove
}

// Method to clear the etire list 
template<class T>
void dLinkedList<T>::clear() {

    while (headPtr != nullptr) { // run the loop unti lthe end is not reached

        dNode<T>* nodetodeletePtr = headPtr; // set the head pointer equal to the node to be deleted
        headPtr = headPtr->getNext(); //set the headpointer to the next pointer in the list
        nodetodeletePtr->setPrev(nullptr); // clear the memory

        nodetodeletePtr->setNext(nullptr);
        delete nodetodeletePtr; //delete the node
        nodetodeletePtr = nullptr; // set it equal to nullptr
    }

    //delete tailPtr;
    tailPtr = nullptr; // set tail ptr equal to nullptr
    //delete headPtr;
    //headPtr = nullptr;

    itemCount = 0;

}

// return the frequency of a given element in the list
template<class T>
int dLinkedList<T>::getFrequencyOf(const T& anEntry) const
{
    int frequency = 0;
    int counter = 0;

    dNode<T>* curPtr = headPtr; // curptr is set to the headPtr
    while (counter <= itemCount && curPtr != nullptr) { // if countter is less than item count and it is not the end of the list

        if (curPtr->getItem() == anEntry) { // get the item at the curPtr and check it with the entry
            frequency++; // if true increase the frequency by 1 
        }
        curPtr = curPtr->getNext(); // get the next pointer to the curPointer and stor it in curPointer
        counter++;
    }
    return frequency; // return frequency 
}


template<class T>
bool dLinkedList<T>::contains(const T& anEntry) const
{
    return (getPointerTo(anEntry) != nullptr);
}

// to insert an element at a given index 
template<class T>
bool dLinkedList<T>::insertAt(const T& newEntry, const int item)
{
    int counter = 0; // Counter is set to 0 
    bool insertion = false; // insertion is set to false 
    dNode<T>* curPtr = headPtr; // cuPtr is set  to the headPtr
    if (item == 0) { // If the insertion is supposed to be in the beginning of the list 
        addFront(newEntry); // calling the add front method and setting insertion equal to true
        insertion = true;
    }
    else if ((item + 1) > itemCount) { // If the insertion is supposed to be at the back of the list 
        addBack(newEntry); // calling the addBack function and setting insertion equal to true
        insertion = true;
    }
    else if (item < itemCount && curPtr != nullptr) { // if the item is supposed to be added in the middle of the list and we are not at the end of the list 
        dNode<T>* newnodeptr = new dNode<T>(); // Create a new node 
        newnodeptr->setItem(newEntry); // set the item in the node equal to newEntry 
        while (curPtr != nullptr) { // if not at the end of the list 
            if (counter == item) { // if we have reached the index where the node is supposed to be inserted at 
                newnodeptr->setItem(newEntry);
                dNode<T>* prevptr = curPtr->getPrev(); // get the previous pointer to the current pointer and store it in PrevPointer
                curPtr->setPrev(newnodeptr); // set the prev of the curPtr to the newNode 
                newnodeptr->setNext(curPtr); // Set the next pointer of the new node to curPtr
                newnodeptr->setPrev(prevptr); // set the prev Pointer to the preptr 
                prevptr->setNext(newnodeptr); // set next of the prevPtr to the new node 
                curPtr = curPtr->getNext(); // get the next pointer
                counter++; // counter ++ 
                insertion = true; // insertion equal to true
                itemCount++; // increase the item count 
            }
            else {
                curPtr = curPtr->getNext();
                counter++;
            }
        }
    }
    else {
        insertion = false;
    }

    return insertion;
}

// Method to remove the value at a given index
template<class T>
bool dLinkedList<T>::removeAt(const int index)
{
    int counter = 0; // counter starts with a zero 
    bool removal = false; // removal is set to false
    dNode<T>* curPtr = headPtr; //curPtr is set to heafPtr
    if (index == 0 && curPtr != nullptr) {
        dNode<T>* nodetodeleteptr = headPtr; // node to be deleted is set to head pinter 
        curPtr = curPtr->getNext(); // curPtr is set to the next pointer
        headPtr = curPtr; // headPtr is set to the curPtr
        curPtr->setPrev(nullptr); // set the previous pointer of the curPointer to nullptr
        nodetodeleteptr->setNext(nullptr);
        delete nodetodeleteptr; // delete the node 
        nodetodeleteptr = nullptr;
        removal = true; // removal is set to true
        itemCount--; // devrease the itemcount by 1 
    }
    else if (index == (itemCount - 1) && curPtr != nullptr) {
        // If the item is supposed to be removed from the back a similar 
        // process i used as in the previous if condition only we use the tailPtr 
        // instead of the headPtr
        dNode<T>* nodetodeleteptr = tailPtr;
        curPtr = tailPtr;
        curPtr = tailPtr->getPrev();
        tailPtr = curPtr;
        curPtr->setNext(nullptr);
        nodetodeleteptr->setPrev(nullptr);
        delete nodetodeleteptr;
        nodetodeleteptr = nullptr;
        removal = true;
        itemCount--;

    }
    else if (index < itemCount && curPtr != nullptr) {
        while (curPtr != nullptr) {
            if (counter == index) {
                // to remove an entry from the middle of the list 
                dNode<T>* nodetodeleteptr = curPtr; // nodetodelete is set to curPtr
                curPtr = curPtr->getPrev(); // get the previous pointer to the current pointer and set it equalt to current pointer
                curPtr->setNext(nodetodeleteptr->getNext()); // curPtr's next pointer is set to nodetodelete's next pointer
                dNode<T>* nextptr = nodetodeleteptr->getNext(); // nextPtr is nodetodelete's next pointer
                nextptr->setPrev(curPtr); // nextptr's previous pointer is equal to curPtr. 

                //Clearing the memory now 
                nodetodeleteptr->setNext(nullptr);
                nodetodeleteptr->setPrev(nullptr);
                curPtr = curPtr->getNext();
                counter++;
                delete nodetodeleteptr;
                nodetodeleteptr = nullptr;
                itemCount--; // Size decreased by 1
                removal = true; // removal set to true 
            }
            else {
                curPtr = curPtr->getNext();
                counter++;
            }
        }
    }
    else {
        removal = false;
    }
    return removal;

}

//works 
template<class T>
bool dLinkedList<T>::replace(const int index, const T& newEntry)
{
    int counter = 0;
    bool itemfound = false;
    T item = NULL; // item is set to NULL
    dNode<T>* curPtr = headPtr;
    if (index < itemCount && curPtr != nullptr) {
        while (!itemfound && curPtr != nullptr) {

            if (counter == index) { // get the index at which the entry is supposed to be replaced
                curPtr->setItem(newEntry); // set the item at that pointer to newEntry
                itemfound = true; // itemfound =true
            }
            else {
                curPtr = curPtr->getNext();
                counter++;
            }
        }
    }

    return itemfound;
}

// works 
// to get the index of a given item
template<class T>
int dLinkedList<T>::getIndex(const T& anEntry) const
{
    int counter = 0;
    bool itemfound = false;
    dNode<T>* curPtr = headPtr;
    while (!itemfound && curPtr != nullptr) {
        if (curPtr->getItem() == anEntry) { // if the item in a given node is equal to the item we ar elooking for 
            itemfound = true; // itemfound is set to true
        }
        else {
            curPtr = curPtr->getNext(); // traversing through the list
            counter++; // counter is increased as we traverse through the list
        }
    }
    if (!itemfound) {
        counter = -1; // is the item could not be found then counter is set to -1
    }

    return counter;
}

//works 6
template<class T>
T dLinkedList<T>::getItem(const int index) const
{
    int counter = 0;
    bool itemfound = false;
    T item = NULL;
    dNode<T>* curPtr = headPtr;
    if (index < itemCount && curPtr != nullptr) {
        while (!itemfound && curPtr != nullptr) {

            if (counter == index) { // traverse the list upto a given index 
                item = curPtr->getItem(); // and get the item at the index and store it in item 
                itemfound = true; // itemfound = true
            }
            else {
                curPtr = curPtr->getNext(); // traversing through the list
                counter++; // index increases as we traverse through the list
            }
        }
    }
    else {
        std::cout << "Invalid index to getItem()" << std::endl;
    }
    return item;
}

//works 
template<class T>
bool dLinkedList<T>::addFront(const T& newEntry)
{
    /*
    dNode<T>* newnodeptr = new dNode<T>();
    newnodeptr->setItem(newEntry);
    headPtr->setPrev(newnodeptr);
    newnodeptr->setNext(headPtr);
    newnodeptr->setPrev(nullptr);
    headPtr = newnodeptr;
    itemCount++;
    */
    add(newEntry); // calling the add fucntion to add in the front of the list 
    return true;
}

//works 4
template<class T>
bool dLinkedList<T>::addBack(const T& newEntry)
{
    if (tailPtr == nullptr) {
        add(newEntry); // if the list empty add function is called to insert the first entry
    }
    else { //else
        dNode<T>* newnodeptr = new dNode<T>(); // a new node is created
        newnodeptr->setItem(newEntry); // the item is inserted in the node
        newnodeptr->setNext(nullptr); // the nodes next pointer is set to nullptr
        newnodeptr->setPrev(tailPtr); // nodes previous pointer is set to nullptr
        tailPtr->setNext(newnodeptr); // tailPtr's next pointer is set to new node
        tailPtr = newnodeptr; // tailPtr is set to new node
        itemCount++;  // size increased by one 
    }

    return true;
}

//works 3
template<class T>
dNode<T>* dLinkedList<T> ::getHead() const
{
    return headPtr;
}

// works
template<class T>
dNode<T>* dLinkedList<T>::getTail() const
{
    return tailPtr;
}

//works 
//The function is used to get a pointer to find a target item in the list and return its pointer
template<class T>
dNode<T>* dLinkedList<T>::getPointerTo(const T& target) const
{
    bool item_found = false;
    dNode<T>* currpointer = headPtr;  // Pointing a node in the List goes
    // The while loop goes to every nod starting from the head until the target_item is found
    while (!item_found && currpointer != nullptr) {

        if (target == currpointer->getItem()) { // If the Item is found, 
            item_found = true; // set item_found to true to exit the loop 
        }
        else {
            currpointer = currpointer->getNext(); // If the item is not found then go to the next node
        }
    }
    return currpointer; // return the pointer to the node where the item was found
}

template<class T>
void dLinkedList<T>::printList() const
{
    std::cout << "Printing out content of list of size: " << itemCount << std::endl;
    std::cout << "The items are: " << "\t";

    dNode<T>* curPtr = headPtr;
    int counter = 0;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
        std::cout << curPtr->getItem() << "\t";
        curPtr = curPtr->getNext();
        counter++;
    }
    std::cout << std::endl;
}

template<class T>
void dLinkedList<T>::printReverseList() const
{
    std::cout << "Printing out (in reverse) content of list with size: " << itemCount << std::endl;
    std::cout << "The items are: " << "\t";

    dNode<T>* curPtr = tailPtr;
    int counter = 0;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
        std::cout << curPtr->getItem() << "\t";
        curPtr = curPtr->getPrev();
        counter++;
    }
    std::cout << std::endl;
}


