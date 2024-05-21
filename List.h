#ifndef SEARCH_AND_SORT_LIST_H
#define SEARCH_AND_SORT_LIST_H

//=================================

#include "Timer.h"

// typedef int index;
const int max_list = 7; //  small value for testing purposes

//=================================

template <class Node_entry>
struct Node {
    //  data members
    Node_entry entry;
    Node<Node_entry> *next;
    //  constructors
    Node();
    explicit Node(Node_entry, Node<Node_entry> *link_next = NULL);
};

template <class List_entry>
Node<List_entry>::Node()
{
    next = NULL;
}

template <class List_entry>
Node<List_entry>::Node(List_entry data, Node<List_entry> *link_next)
{
    entry = data;
    next = link_next;
}

template <class List_entry>
class List {
public:
    //  Specifications for the methods of the list ADT go here.

    List();
    size_t size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void(*visit)(List_entry &));
    Error_code retrieve(int position, List_entry &x) const;
    Error_code replace(int position, const List_entry &x);
    Error_code remove(int position, List_entry &x);
    Error_code insert(int position, const List_entry &x);

    //  The following methods replace compiler-generated defaults.
    ~List();
    List(const List<List_entry> &copy);
    void operator =(const List<List_entry> &copy);
protected:
    //  Data members for the linked list implementation now follow.
    int count;
    Node<List_entry> *head;

    //  The following auxiliary function is used to locate list positions
    Node<List_entry> *set_position(int position) const;

};

template <class List_entry>
List<List_entry>::List()
//Post: The List is initialized to be empty.
{
    count = 0;
    head = NULL;
}

template <class List_entry>
List<List_entry>::~List()
// Post: The List is empty: all entries have been removed.
{
    clear();
}

template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
// Post: The List is initialized as a copy of List copy.
{
    count = copy.count;
    Node<List_entry> *new_node, *old_node = copy.head;

    if (old_node == NULL) head = NULL;
    else {
        new_node = head = new Node<List_entry>(old_node->entry);
        while (old_node->next != NULL) {
            old_node = old_node->next;
            new_node->next = new Node<List_entry>(old_node->entry);
            new_node = new_node->next;
        }
    }
}

template <class List_entry>
size_t List<List_entry>::size() const {
    return static_cast<size_t>(count);
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List, the function succeeds:
Any entry formerly at position and all later entries have their position numbers increased by 1, and
x is inserted at position of the List.
Else:
The function fails with a diagnostic error code.
*/
{
    if (position < 0 || position > count)
        return utility_range_error;
    Node<List_entry> *new_node, *previous, *following;
    if (position > 0) {
        previous = set_position(position - 1);
        following = previous->next;
    }
    else following = head;
    {
        new_node = new Node<List_entry>(x, following);
    }
    if (new_node == NULL)
        return overflow;
    if (position == 0)
        head = new_node;
    else
        previous->next = new_node;
    count++;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
// Post: If the List is not empty and 0 <= position < n, where n is the number of entries in the List,
{
    Node<List_entry> *prior, *current;
    if (count == 0) return fail;
    if (position < 0 || position >= count) return range_error;

    if (position > 0) {
        prior = set_position(position - 1);
        current = prior->next;
        prior->next = current->next;
    }

    else {
        current = head;
        head = head->next;
    }

    x = current->entry;
    delete current;
    count--;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
// Post: If 0 <= position < n, where n is the number of entries in the List,
{
    Node<List_entry> *current;
    if (position < 0 || position >= count) return range_error;
    current = set_position(position);
    x = current->entry;
    return success;
}

template <class List_entry>
void List<List_entry>::clear()
// Post: The List is empty: all entries have been removed.
{
    Node<List_entry> *p, *q;

    for (p = head; p; p = q) {
        q = p->next;
        delete p;
    }
    count = 0;
    head = NULL;
}

template <class List_entry>
Node<List_entry> *List<List_entry>::set_position(int position) const
/*
Pre:   position is a valid position in the List;
0 <= position < count.
Post: Returns a pointer to the Node in position.
*/
{
    Node<List_entry> *q = head;
    for (int i = 0; i < position; i++) q = q->next;
    return q;
}

template <class List_entry>
void List<List_entry>::operator =(const List<List_entry> &copy)
// Post: The List is assigned to copy a parameter
{
    List new_copy(copy);
    clear();
    count = new_copy.count;
    head = new_copy.head;
    new_copy.count = 0;
    new_copy.head = NULL;
}

#endif //SEARCH_AND_SORT_LIST_H
