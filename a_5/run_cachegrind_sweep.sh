#!/bin/bash

EXE=./matvec_blocked
N=2048
BS=(1 2 4 8 16 32 64 128 256)   


for B in "${BS[@]}"; do
  echo "=== Running Cachegrind for B=${B} ==="

  OUT_RAW=cachegrind.out.B_${B}
  OUT_ANNOT=cg_B_${B}.txt
  OUT_STD=matvec_B_${B}.stdout

  # Run under Cachegrind with data-cache simulation enabled
  valgrind --tool=cachegrind \
           --cache-sim=yes \
           --branch-sim=no \
           --I1=32768,8,64 \
           --D1=32768,8,64 \
           --LL=8388608,16,64 \
           --cachegrind-out-file=${OUT_RAW} \
           ${EXE} ${N} ${B} > ${OUT_STD} 2>&1

  # Annotate results to human-readable text
  cg_annotate ${OUT_RAW} > ${OUT_ANNOT}

  # Extract PROGRAM TOTALS block for quick inspection
  echo "PROGRAM TOTALS for B=${B}:"
  grep -A3 "PROGRAM TOTALS" ${OUT_ANNOT} | head -n 8
  echo "------------------------------------------------------"
done