#include <iostream>
#include "Stack.h"
using namespace std;

template <class Arbitrary>
Arbitrary * Stack<Arbitrary> :: Pop (void) {
        return this->Remove (END);
}

template <class Arbitrary>
Arbitrary * Stack<Arbitrary> :: Push (Arbitrary * element) {
        return this->Insert (element, END);
}

template <class Arbitrary>
Arbitrary * Stack<Arbitrary> :: Top (void) const {
        return this->View (END);
}
