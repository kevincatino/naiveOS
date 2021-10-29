#!/bin/bash

make --no-print-directory clean
make --no-print-directory all
cd Toolchain
make --no-print-directory clean
make --no-print-directory all
cd ..