#!/bin/bash  
make clean && make
./test
gprof --demangle -b -p ./test
