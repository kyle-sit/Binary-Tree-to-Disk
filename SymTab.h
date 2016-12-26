#ifndef SYMTAB_H
#define SYMTAB_H

/* DO NOT CHANGE:  This file is used in evaluation */

#include <iostream>
#include "Tree.h"
using namespace std;

template <class Whatever>
class SymTab : private Tree<Whatever> {
public:
        SymTab (const char * datafile) : Tree<Whatever> (datafile) {}
        using Tree<Whatever> :: GetCost;
        using Tree<Whatever> :: GetOperation;
        using Tree<Whatever> :: Insert;
        using Tree<Whatever> :: Lookup;
        using Tree<Whatever> :: Remove;
        using Tree<Whatever> :: Set_Debug_On;
        using Tree<Whatever> :: Set_Debug_Off;
        using Tree<Whatever> :: Write;
};

#endif
