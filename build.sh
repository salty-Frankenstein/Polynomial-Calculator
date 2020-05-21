#!/bin/bash
cd build
cmake ..
make
mv cal ../env
cd ../env
./cal
rm cal
cd ..

