# !/bin/sh

g++ src/key-gen.cpp -o bin/key-gen
g++ src/test.cpp -o bin/test -I./include
./bin/key-gen
./bin/test

exit
