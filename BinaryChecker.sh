#!/bin/bash

echo "Initialize testing ........."

if ! test -d ~/hw9/binaryfiles ; then
  mkdir ~/hw9/binaryfiles; 
fi

make fresh

#creating remove root result for student and instructor
~/hw9/Driver [-x] < ~/hw9/outputfile > ~/hw9/results/my_result

od -x ~/hw9/Driver.datafile > ~/hw9/binaryfiles/my_binary

make fresh

~/../public/hw9/Driver [-x]  < ~/hw9/outputfile > ~/hw9/results/public_result

od -x ~/hw9/Driver.datafile > ~/hw9/binaryfiles/public_binary


#comparing 
cmp --quiet ~/hw9/results/my_result ~/hw9/results/public_result
if [ $? == 0 ]; then
  echo "outputfile test - Pass"
else
  echo "outputfile test - Failed"
  echo "Please check your incorrect output at ~/hw9/results/my_result"
fi

#comparing 
cmp --quiet ~/hw9/binaryfiles/my_binary ~/hw9/binaryfiles/public_binary
if [ $? == 0 ]; then
  echo "Driver.datafile check - Pass"
else
  echo "Driver.datafile check - Failed"
  echo "To see which part of your Driver.datafile is different than instructor's result"
  echo "Please run: diff ~/hw9/binaryfiles/my_binary ~/hw9/binaryfiles/public_binary"
fi


