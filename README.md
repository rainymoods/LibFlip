# Artifacts for IEEE S&P 2027

The artifacts for the paper "Undermining Multimodal Perception in Autonomous Driving Systems via Shared Library Fault Injection", submitted to IEEE S&P 2027.

## 1. Structural Overview

According to Appendix B, this repository includes the following source code and evaluation results:

* `BLASAnalyzer/`: The source code for identifying vulnerable instructions, as discussed in **Section 4.1 Offline Vulnerable Instruction Identification**.
* `DRAMScanner/`: The source code employed during the memory profiling in **Section 4.2 Online End-to-End Fault Injection Attack**.
* `MemScanRes/`: The identified flippable memory bit sample in the Micron DRAM module shown in **Section 5.3 The Memory Bit Flip Results**.
* `ModelAtkRes/`: The perception results of different object detection models presented in **Section 5.4 ADS Perception System Attack Results**.

## 2. Artifact Details

### 2.1 BLASAnalyzer
* **Introduction:**

  ​	This code compiles the original `OpenBLAS` source code into the intermediate representation for analysis, identifies branch instructions and performs semantic inversion on them, and then recompiles the modified code into patched libraries for offline evaluation of attack effects on ADS perception systems.

* **Prerequisites:**

  ​	The `OpenBLAS` codebase.
  ​	`gcc 11.x`, `clang 12.x`, `cmake 3.16.0`

* **Description of sub-folders:**

  * `ground_truth/:`The code for analyzing *driver layer* SGEMM functions in `OpenBLAS`.
  * `ground_truth/:`The code for analyzing *kernel layer* SGEMM functions in `OpenBLAS`.

* **Quick Starts:**

​			Please refer to the `README` files within the respective sub-folders for detailed steps on running the code.

### 2.2 DRAMScanner

- **Introduction:**

​			This tool is designed to scan the DRAM for flippable bit information, including physical addresses, DRAM locations, and flip directions.

- **Prerequisites:**

​			`g++ 8.x`, `cmake 3.14.x`

- **Quick Starts:**

​			Please refer to the `README` files within the respective sub-folders for detailed steps on running the code.

### 2.3 MemScanRes

- **Introduction:**

​			Results of a 768 MB memory scan on the Micron DRAM module, including the information of flippable memory bits about their physical addresses, page offsets, DRAM locations, and flip directions of flippable memory bits.

- **Tips:**

​			To facilitate analysis, the results are partitioned into multiple files, each containing data for a 128 MB memory region.

### 2.4 ModelAtkRes

- **Introduction:**

​			LibFlip's sample attack results on different object detection models implemented with different ML frameworks. For each model, the artifact provides attack results obtained by exploiting all identified branch instructions in the SGEMM functions. The resulting attack effects include perception failures, system anomalies, and ineffective attacks.

- **Tips:**

​	for , just sample results on a single scene















