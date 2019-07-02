#!/bin/bash

gcc rf_to_matrix.c -o get_map
./get_map > parcial_map
./comp.sh maze.cpp maze
