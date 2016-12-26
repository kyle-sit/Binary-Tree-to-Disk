/**************************************************************************** 

																															Kyle Sit 
																															Sid Ambulkar
																															CSE 12, Fall 
																															22 November 2015 
																															cs12xgj & cs12xaa
																	Assignment Nine 

	File Name:      Driver.c
	Description:    This program is the executable to manipulate the tree.
 ****************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <getopt.h>
#include "Driver.h"
#include "SymTab.h"
#include <fstream> 

using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

ostream & operator << (ostream & stream, const UCSDStudent & stu) {
        return stream << "name:  " << stu.name
                << " with studentnum:  " << stu.studentnum;
}

int main (int argc, char * const * argv) {
        char buffer[BUFSIZ];
        char command;
        long number;
        char option;
       
				//create input and output stream pointers
				istream * input = &cin;
				ostream * output = &cout;

        SymTab<UCSDStudent>::Set_Debug_Off ();

        while ((option = getopt (argc, argv, "x")) != EOF) {

        switch (option) {
                case 'x': SymTab<UCSDStudent>::Set_Debug_On ();
                        break;
                }       
        }
        
        SymTab<UCSDStudent> ST("Driver.datafile");
        ST.Write (cout << "Initial Symbol Table:\n" );

        while (cin) {
								//check for end of input
								if(!(*input)) {
									//if end of cin input, break
									if(input == &cin) {
										break;
									}
									
									//else input from file is complete
									else {
										//selete pointers to files
										//set to defaults

										delete input;
										input = &cin;

										delete output;
										output = &cout;
									}
								}

                command = NULL;         // reset command each time in loop
                (* output) << "Please enter a command ((i)nsert, "
                        << "(l)ookup, (r)emove, (w)rite), (f)ile:  ";
                (* input) >> command;

                switch (command) {
								//case for file input
								case 'f': {
												//user prompt
												(* output) << "Please enter file name for commands:  ";
												//read in filename from buffer
												(* input) >> buffer; //formatted input
												//set file to input
												input = new ifstream(buffer);
												//set output to /dev/null
												output = new ofstream("/dev/null");
												break;
								}

                case 'i': {
                        (* output) << "Please enter UCSD student"
																				<< " name to insert:  ";
                        (* input) >> buffer;  // formatted input

                        (* output) << "Please enter UCSD student number:  ";
                        (* input) >> number;

                        UCSDStudent stu (buffer, number);

                        // create student and place in symbol table
                        ST.Insert (stu);
                        break;
                }
                case 'l': { 
                        unsigned long found;    // whether found or not

                        (* output) << "Please enter UCSD student name to" 
																		<< "lookup:  ";
                        (* input) >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        found = ST.Lookup (stu);
                        
                        if (found)
                                cout << "Student found!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                        }
                case 'r': { 
                        unsigned long removed;

                        cout << "Please enter UCSD student name to remove:  ";
                        (* input) >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        removed = ST.Remove(stu);

                        if (removed)
                                cout << "Student removed!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                }
                case 'w': 
                        ST.Write (cout << "The Symbol Table contains:\n");
                }
        }

        ST.Write (cout << "\nFinal Symbol Table:\n");
				
				//print out of cost and operation information
				if (ST.GetOperation() != 0) {
					cout << "\nCost of operations: ";
					cout << ST.GetCost();
					cout << " tree accesses";

					cout << "\nNumber of operations: ";
					cout << ST.GetOperation();

					cout << "\nAverage cost: ";
					cout << (((float)(ST.GetCost()))/(ST.GetOperation()));
					cout << " tree accesses/operation\n";
				}

				else {
					cout << "\nNo cost information available.\n";
				}
		
}
