# DRAMReverser

## Overview

The source code and results of the DRAM address mapping function reverse engineering.

## Directory Details

#### 1. `code/`

* **Objective:** 

  Source code for reverse-engineering DRAM mapping functions.

* **Usage:** 

  Detailed execution commands and parameters are documented in `code/README.md`.

#### 2. `results/`

* **Objective:** 

  ​	Analysis results obtained on the Intel Core i7-6700.

* **Components:**

  * `exec_log.txt`: The execution log, which details the recovered bank conflict functions and row address masks.
  * `access.csv`: Measured access times for inferring DRAM bank and row address mappings.
  * `threshold.png`: Histogram visualization highlighting memory access latency distributions.

---

## Integration Guidelines

Execution outputs from this module should be imported into the corresponding configuration structures within the `DRAMHammer`. Refer to `DRAMHammer/README.md` for integration details

.