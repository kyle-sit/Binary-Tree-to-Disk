#include <cctype>
#include <iostream>
#include <cstdio>
#include <string>
#include "Calc.h"
#include "Decin.h"
#include "Namein.h"
#include "Stack.h"
using namespace std;

static char operators[] = "= ()+-*/^ !";

static long add (long, long);
static long divide (long, long);
static long exponent (long, long);
static long fact (long, long ignored);
static long mult (long, long);
static long sub (long, long);

static long (*functions[]) (long, long) =
        { NULL, NULL, NULL, NULL, add, sub, mult, divide, exponent, NULL, fact };

Variable * assign (Variable * variable, long value) {
        
        // give variable its value
        variable->value = value;
        return variable;
}

long Calculator :: Eval (void) {
        Word * op1, * op2;              /* the operands */
        long operand1, operand2;        /* the operands as long */
        Word * operation;               /* the operation being performed */
        long result;                    /* result of computation */

        /* reverse stack1 onto stack2 */
        while (!stack1.IsEmpty ())
                stack2.Push (stack1.Pop ());

        while (!stack2.IsEmpty ()) {


                /* numbers and variables go to stack1 */
                if (!(stack2.Top ())->isoperator ())
                        stack1.Push (stack2.Pop ());
                
                /* operand found */
                else {
                        operation = stack2.Pop ();
                        
                        /* get operands */
                        op1 = stack1.Pop ();
                        operand1 = (op1->isvariable ())
                                ? symtab.Lookup (*(op1->var)),op1->var->value
                                : op1->value;

                        if (operation->op->ascii != '!') {
                                op2 = stack1.Pop ();
                                if (op2->isvariable ()
                                && (operation->op->ascii != '=')) {

                                        symtab.Lookup (*(op2->var)),
                                        operand2 = op2->var->value;
                                }
                                else
                                        operand2 = op2->value;
                        }
                        else
                                operand2 = operand1;

                        /* evaluate expression and push to stack1 */
                        if (operation->op->ascii != '=')
                                result = functions[operation->op->index]
                                        (operand1, operand2);
                        // variable assignment
                        else {
                                symtab.Insert (*assign (op2->var, operand1));
                                result = op2->var->value;
                        }

                        stack1.Push (new Word (result));

                        /* free up memory */
                        delete op1;
                        if (operation->op->ascii != '!')
                                delete op2;
                        delete operation;
                }
        }

        op1 = stack1.Pop ();
        result = (op1->isvariable ())
                ? symtab.Lookup (*(op1->var)), op1->var->value
                : op1->value;

        /* free up memory */
        delete op1;

        return result;
}

long Calculator :: InToPost (void) {
        char character;                 /* character input from the user */
        Word * word;                    /* a word for the stack */
        char variable_name [BUFSIZ];    /* to hold variable's name */
        
        while ((character = cin.get ()) != '\n') {

                /* check for termination of input */
                if (character == EOF)
                        return EOF;

                /* ignore blanks */
                if (isspace (character))
                        continue;
                
                if (isdigit (character) || character == '.') {

                        /* for decin call */
                        cin.putback (character);

                        /* place any numbers onto stack1 */

                        stack1.Push (new Word (decin()));
                }

                else if (isalpha (character)) {

                        /* for namein call */
                        cin.putback (character);

                        /* place any numbers onto stack1 */

                        stack1.Push (new Word (namein (variable_name)));
                }

                else if (character == '(') {

                        /* open parenthesis go onto stack2 */

                        stack2.Push (new Word ('('));
                
                }
                else if (character == ')') {

                        /* pop stack2 to stack1 until matching parenthesis is found */
                        while (word = stack2.Pop (), word->op->ascii != '(')
                                stack1.Push (word);

                        /* free up memory */
                        delete word;
                }

                /* operator must be encountered */
                else {
                        word = new Word (character);/* to store on stack */

                        /* pop stack2 to stack1 until empty or lower priority */
                        while (!stack2.IsEmpty () &&
                                (stack2.Top ())->op->priority
                                        >= word->op->priority)
                                        stack1.Push (stack2.Pop ());

                        /* finally place operator on stack2 */
                        stack2.Push (word);
                }
        }

        /* place any remaining stack2 items to stack1 ==> done */
        while (!stack2.IsEmpty ())
                stack1.Push (stack2.Pop ());
        
        return 1;
}

Operator :: Operator (char ascii_code) : ascii (ascii_code) {
        
        index = 0;      /* index of the operand in character array */

        /* compute function index */
        while (operators[index] != ascii)
                index++;

        priority = index >> 1;
}

ostream & operator << (ostream & stream, const Calculator & ccc) {

        ccc.stack1.Write (stream << "Stack 1 is:\n");
        ccc.stack2.Write (stream << "Stack 2 is:\n");
        return ccc.symtab.Write (stream << "Symbol Table is:\n");
}

ostream & operator << (ostream & stream, const Operator & ooo) {

        return stream << ooo.ascii;
}

ostream & operator << (ostream & stream, const Variable & variable) {

    return stream << variable.name << "(" << variable.value << ")";
}

ostream & operator << (ostream & stream, const Word & word) {

        switch (word.type) {
        case OPERATOR:
                stream << *(word.op) << " ";
                break;
        case VALUE:
                stream << word.value << " ";
                break;
        case VARIABLE:
                stream << *(word.var) << " ";
        }

        return stream;
}

ostream & Calculator :: Write_Postfix (ostream & stream) const {
        return stack1.Write (stream);
}

static long add (long xxx, long yyy) {
        return xxx + yyy;
}

static long divide (long divisor, long dividend) {
        return dividend / divisor;
}

static long exponent (long power, long xxx) {
        long retval = 1;

        while (power > 0) {
                retval *= xxx;
                power--;
        }
        
        while (power < 0) {
                retval /= xxx;
                power++;
        }

        return retval;
}

static long fact (long xxx, long ignored) {
        return (xxx <= 1) ? 1 : xxx * fact (xxx - 1, ignored);
}

static long mult (long factorx, long factory) {
        return factorx * factory;
}

static long sub (long xxx, long yyy) {
        return yyy - xxx;
}
