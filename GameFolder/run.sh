#!/bin/bash
rm -rf build
mkdir build
cd build || exit
cmake ../
make
chmod +x Pacman
./Pacman
