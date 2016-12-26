#ifndef TREE_H
#define TREE_H

/* DO NOT CHANGE:  This file is used in evaluation */

#include <fstream>
#include <iostream>
using namespace std;

typedef long offset;

template <class Whatever>
struct TNode;

template <class Whatever>
class Tree {
        friend struct TNode<Whatever>;
        static long cost;
        static int debug_on;
        fstream * fio;
        long occupancy;
        static long operation;
        offset root;
        unsigned long tree_count;
        void ResetRoot (void);

public:
        Tree (const char *);
        ~Tree (void);

        static long GetCost ();
        static long GetOperation ();
        static void IncrementCost ();
        static void IncrementOperation ();
        static void Set_Debug_On (void);
        static void Set_Debug_Off (void);

        unsigned long Insert (Whatever &);
        unsigned long Lookup (Whatever &) const;
        unsigned long Remove (Whatever &);
        ostream & Write (ostream &) const;
};

#include "Tree.c"

#endif
