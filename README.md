# Artifacts for USENIX Security 2027

The artifacts for the paper **"Undermining Multimodal Perception in Autonomous Driving Systems via Shared Library Fault Injection"**, submitted to USENIX Security 2027.

## 1. Structural Overview

According to **Open Science** in the paper, this repository includes the following source code and evaluation results:

- `BLASAnalyzer/`: The source code for identifying vulnerable instructions, as discussed in **Section 4.1 Offline Vulnerable Bit Identification**.
- `DRAMHammer/`: The source code employed for identifying effective hammering patterns and triggering bit flips in **Section 4.2 Online End-to-End Fault Injection Attack**.
- `DRAMReverser/`: The source code and results of the DRAM address mapping function reverse engineering in **Section 4.2 Online End-to-End Fault Injection Attack**.
- `MemScanRes/`: The identified effective hammering patterns and flippable memory bit results shown in **Section 5.3 The Memory Bit Flip Results**.
- `ModelAtkRes/`: The fault injection results of different object detection models presented in **Section 5.4 ADS Perception System Attack Results**.

## 2. Artifact Details

### 2.1 BLASAnalyzer

- **Introduction:**

  ​	This project compiles the original `OpenBLAS` source code into the intermediate representation for analysis, identifies branch instructions and performs semantic inversion on them, and then recompiles the modified code into patched libraries for offline evaluation of attack effects on ADS perception systems. Further details are discussed in **Section 4.1 Offline Vulnerable Bit Identification**.

- **Prerequisites:**

  ​	The `OpenBLAS` codebase. 	`gcc 11.x`, `clang 12.x`, `cmake 3.16.x`

- **Description of sub-folders:**

  - `ground_truth/:` The code for analyzing `kernel layer` SGEMM functions in `OpenBLAS` (i.e., the *sgemm_kernel and sgemm_beta* functions).
  - `ground_truth_alpha/:` The code for analyzing `interface layer` and `driver layer` SGEMM functions in `OpenBLAS` (i.e., the *cblas_sgemm, sgemm_nn, sgemm_nt, sgemm_tn, and sgemm_tt* functions).

- **Quick Starts:**

  ​		Please refer to the `README` files within the respective sub-folders for detailed steps on running the code.

### 2.2 DRAMHammer

- **Introduction:**

  ​	This tool is designed to identify effective hammering patterns and trigger Rowhammer attacks on DRAM for tasks such as collecting flippable bit information (e.g., physical addresses, DRAM locations, and flip directions). The detailed procedure is explained in **Section 4.2 Online End-to-End Fault Injection Attack**.

- **Prerequisites:**

  ​    `g++ 8.x`, `cmake 3.14.x`

- **Quick Starts:**

  ​    Please refer to the `README` files within the respective sub-folders for detailed steps on running the code.

### 2.3 DRAMReverser

- **Introduction:**

  ​    Performing the DRAM address mapping function reverse engineering task shown in **Section 4.2 Online End-to-End Fault Injection Attack**.

- **Description of sub-folders:**

  - `code/:` The code for reverse-engineering the address mapping functions.
  - `results/:` The results obtained by the analysis on the Intel Core i7-6700 CPU.

- **Quick Starts:**

  ​    Please refer to the `README` files within the respective sub-folders for detailed steps on running the code.

### 2.4 MemScanRes

- **Introduction:**

  ​    The identified representative effective hammering patterns and the located flippable bits within the Micron DRAM presented in **Section 5.3 The Memory Bit Flip Results**.

- **Description of sub-folders:**

  - `hammer_patterns/:` Representative memory hammering patterns identified by DRAMHammer.
  - `hammer_results/:` Results of a 768 MB memory scan on the Micron DRAM module, including the information of flippable memory bits about their physical addresses, page offsets, DRAM locations, and flip directions of flippable memory bits.

- **Tips:**

  ​    To facilitate analysis, the results are partitioned into multiple files, each containing data for a 128 MB memory region.

### 2.5 ModelAtkRes

- **Introduction:**

  ​    LibFlip's sample attack results on different object detection models implemented with different ML frameworks. For each model, the artifact provides attack results obtained by exploiting 139 branch instructions in the SGEMM functions. Each sub-file corresponds to the attack results obtained by flipping a single branch instruction, while the attack effects include perception failures, system anomalies, and ineffective attacks. More details are provided in  **Section 5.4 ADS Perception System Attack Results**.

- **Description of sub-folders:**

  - `caffe-yolox/:` Perception results of attacks on the `Caffe-based YOLOX3D` model.

    - `auto_results:` Perception results under the semantic inversion of 116 branch instructions in the `interface layer` and `driver layer` SGEMM functions. Each sub-file corresponds to the attack results obtained by flipping a single branch instruction.
    - `auto_kernel_results:` Perception results under the semantic inversion of 23 branch instructions identified in the `kernel layer` SGEMM functions. Each sub-file corresponds to the attack results obtained by flipping a single branch instruction.

  - `torch-yolox/:` Perception results of attacks on the `PyTorch-based YOLOX3D` model.

    ​		The directory structure and file descriptions are identical to those in the `caffe-yolox/` folder.

  - `torch-ssd/:` Perception results of attacks on the `PyTorch-based SSD` model.

    ​		The directory structure and file descriptions are identical to those in the `caffe-yolox/` folder.

- **Tips:**

  ​    Given the complexity of the full evaluation results, here we provide the perception results of the models on a single `nuScenes` scene to facilitate understanding.

<br>
