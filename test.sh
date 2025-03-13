#!/bin/bash

make

# generate matrices
# for k in 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400; do
#   python3 generate_matrix.py $k a$k.mat
#   python3 generate_matrix.py $k b$k.mat
# done


# of threads, size of array
for i in 1 2 3 4 5 6 7 8 10 12 14 16 32 64 128 256 512 1024; do 
  #touch "output_t$i.csv"
  for j in 100 200 300 400 500 600 700 800 900 1000 ; do
    ./matrix_program $i $j | tee -a naive_output.csv naive_threads_output_t$i.csv

  done
done