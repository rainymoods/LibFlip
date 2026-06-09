# Code Description

This tool is used to identify branch instructions within the `sgemm_kernel` and `sgemm_beta` functions and compile each flip case to shared libraries.

The core code for instruction flipping is stored in `llvm-pass/flipBranches` and `llvm-pass/flipLauncher`.

# Tips for Getting Started

1. Replace the Makefile in the current directory: substitute `XXXX` with your own path.

2. Replace `XXXX` with your own path in `./openblas/build/Makefile` and `./openblas/build/kernel/Makefile`.

3. Then, execute `make ground_truth` in the current directory to perform the flipping.
