#ifndef LIST_H
#define LIST_H

/* DO NOT CHANGE:  This file is used in evaluation */

#include <iostream>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

template <class Arbitrary>
struct LNode;

template <class Arbitrary>
class List {
        LNode<Arbitrary> * end;
        long occupancy;
public:
        List (void) : end (NULL), occupancy (0) {}
        ~List (void);
        Arbitrary * Insert (Arbitrary *, long);
        Arbitrary * Remove (long);
        Arbitrary * View (long) const;
        long IsEmpty (void) const {
                return ! NumElements ();
        }
        long NumElements (void) const {
                return occupancy;
        }
        ostream & Write (ostream &) const;
};

/* where to insert, view, remove */
#define FRONT 0
#define END 1

#include "List.c"

#endif
