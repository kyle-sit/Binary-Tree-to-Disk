#include <iostream>
#include "List.h"
using namespace std;

template <class Arbitrary>
struct LNode {
        Arbitrary * data;
        LNode<Arbitrary> * pre;
        LNode<Arbitrary> * next;

        LNode (Arbitrary * element) : data (element), pre (NULL), next (NULL) {}
        ~LNode (void);
};

template <class Arbitrary>
ostream & operator << (ostream & stream, const LNode<Arbitrary> & nnn) {
        return stream << *(nnn.data);
}

template <class Arbitrary>
List<Arbitrary> :: ~List (void) {
        Arbitrary * data;               /* working Arbitrary pointer */

        /* empty list */
        while (occupancy) {

                /* remove top element from list */
                data = Remove (END);

                /* delete data element */
                delete data;
        }
}

template <class Arbitrary>
Arbitrary * List<Arbitrary> :: Remove (long where) {
        LNode<Arbitrary> * old_node;            /* working node */
        Arbitrary * retval;

        /* check status of list */
        if (!occupancy) {
                cerr << "Popping from an empty list!!!\n";
                return NULL;
        }

        /* adjust END if necessary to always remove from the FRONT */
        if (where == END)
                end = end->pre;

        old_node = end->next;
        retval = old_node->data;

        /* remove old_node from list */
        old_node->next->pre = end;
        end->next = old_node->next;

        /* delete the empty node */
        delete old_node;

        /* update occupancy */
        occupancy--;

        return retval;
}

template <class Arbitrary>
Arbitrary * List<Arbitrary> :: Insert (Arbitrary * element, long where) {
        Arbitrary * retval;
        LNode<Arbitrary> * new_node;

        /* store element in a LNode */
        new_node = new LNode<Arbitrary> (element);
        retval = new_node->data;

        /* is this the only element in the list??? */
        if (!occupancy)
                end = new_node->next = new_node->pre = new_node;
        
        else {
                new_node->next = end->next;
                new_node->pre = end;
                end->next->pre = new_node;
                end->next = new_node;
        }

        if (where == END)
                end = end->next;

        /* update occupancy */
        occupancy++;

        return retval;
}

template <class Arbitrary>
Arbitrary * List<Arbitrary> :: View (long where) const {

        /* empty list */
        if (!occupancy)
                return NULL;

        return (where == END) ? end->data : end->next->data;
}

template <class Arbitrary>
ostream & List<Arbitrary> :: Write (ostream & stream) const {
        long count;             /* to know how many elements to print */
        LNode<Arbitrary> * current;             /* working node */

        if (occupancy > 0)
                current = end->next;

        for (count = 1; count <= occupancy; count++) {
                stream << *current;
                current = current->next;
        }
                
        return stream;
}

template <class Arbitrary>
LNode<Arbitrary> :: ~LNode (void) {
        data = NULL;
        next = pre = NULL;
}
