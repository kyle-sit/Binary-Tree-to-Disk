#!/bin/bash

echo "Initialize testing ........."

if ! test -d ~/hw9/results ; then
  mkdir ~/hw9/results; 
fi


#creating generate IRL result for student and instructor
~/../public/GenerateIRL -o 1000 > ~/hw9/outputfile2

make fresh

~/hw9/Driver [-x] < ~/hw9/outputfile2 > ~/hw9/results/my_result2

make fresh

~/../public/hw9/Driver [-x]  < ~/hw9/outputfile2 > ~/hw9/results/public_result2

make fresh

#creating remove root result for student and instructor
~/hw9/Driver [-x] < ~/hw9/outputfile > ~/hw9/results/my_result

make fresh

~/../public/hw9/Driver [-x]  < ~/hw9/outputfile > ~/hw9/results/public_result

make fresh

#creating alphabet result for student and instructor
~/hw9/Driver [-x] < ~/hw8/alphabet > ~/hw9/results/my_alphabet_result

make fresh

~/../public/hw9/Driver [-x]  < ~/hw8/alphabet > ~/hw9/results/public_alphabet_result

make fresh

#creating alphabet.rev result for student and instructor
~/hw9/Driver [-x] < ~/hw8/alphabet.rev > ~/hw9/results/my_alphabet.rev_result

make fresh

~/../public/hw9/Driver [-x] < ~/hw8/alphabet.rev > ~/hw9/results/public_alphabet.rev_result


#comparing 
cmp --quiet ~/hw9/results/my_result2 ~/hw9/results/public_result2
if [ $? == 0 ]; then
  echo "GenerateIRL test - Pass"
else
  echo "GenerateIRL test - Failed"
  echo "Please check your incorrect output at ~/hw9/results/my_result2"
fi


#comparing 
cmp --quiet ~/hw9/results/my_result ~/hw9/results/public_result
if [ $? == 0 ]; then
  echo "outputfile test - Pass"
else
  echo "outputfile test - Failed"
  echo "Please check your incorrect output at ~/hw9/results/my_result"
fi


#comparing student's alphabet result with instructor's
cmp --quiet ~/hw9/results/my_alphabet_result ~/hw9/results/public_alphabet_result
if [ $? == 0 ]; then
  echo "alphebet test - Pass"
else
  echo "alphebet test - Failed"
  echo "Please check your incorrect output at ~/hw9/results/my_alphabet_result"
fi


#comparing student's alphabet.rev result with instructor's
cmp --quiet ~/hw9/results/my_alphabet.rev_result ~/hw9/results/public_alphabet.rev_result
if [ $? == 0 ]; then
  echo "alphabet.rev test - Pass"
else
  echo "alphabet.rev test - Failed"
  echo "Please check your incorrect output at ~/hw9/results/my_alphabet.rev_result"
fi

