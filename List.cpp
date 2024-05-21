#include "List.h"


template <class List_entry>
bool List<List_entry>::empty() const
// Post: Return true if the List is empty; otherwise, return false.
{
    return count == 0;
}

template <class List_entry>
bool List<List_entry>::full() const
// Post: Return true if the List is full; otherwise, return false.
{
    return false;
}

template <class List_entry>
void List<List_entry>::traverse(void(*visit)(List_entry &))
{
    Node<List_entry> *q;

    for (q = head; q; q = q->next)
        (*visit)(q->entry);
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
    Node<List_entry> *current;
    if (position < 0 || position >= count) return range_error;
    current = set_position(position);
    current->entry = x;
    return success;
}














