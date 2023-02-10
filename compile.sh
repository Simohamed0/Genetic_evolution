#!/bin/bash

# if [ "$1" == "rm" ]; then
#   rm *.log
#   rm CMakeLists.txt
# else 
#   easena $1.ez
#   make 
#   ./$1 --nbCPUThreads 20 --seed 2
#   make easeaclean
# fi

easena -gp findfunc.ez
make
./findfunc --nbCPUThreads 10 --seed 2

