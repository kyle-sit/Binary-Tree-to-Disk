#include <iostream>
#include <getopt.h>
#include "Calc.h"
using namespace std;

int main (int argc, char * const * argv) {

        char option;
        
        SymTab<Variable>::Set_Debug_Off();

        while ((option = getopt (argc, argv, "x")) != EOF) {

        switch (option) {
                case 'x': SymTab<Variable>::Set_Debug_On();
                        break;
                }       
        }

        Calculator calc ("Calc.datafile");      // Calculator to use

        while (1) {
                cout << "\nPlease enter an expression to calculate:  ";
                if (calc.InToPost () == EOF)
                        break;
                
                calc.Write_Postfix
                        (cout << "\nThe expression in postfix order is:  ");

                cout << "\nwhich evaluates to:  " << calc.Eval () << "\n";

                cerr << "Calculator is:\n" << calc;
        }
        cout << "\n";
}
