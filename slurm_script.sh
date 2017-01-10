#!/bin/bash
#SBATCH --job-name=AntonJob
#SBATCH --account=aroth
#SBATCH -N 4
#SBATCH --tasks-per-node=4                                      #       number  of      processes       per     node    
#SBATCH -o      process_mpi_%j.out                      #       output  file    
#SBATCH -e      process_mpi_%j.err                      #       error   messages 

cat $0

./build/collimator macros/run3.mac
