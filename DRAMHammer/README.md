# DRAMHammer

## Overview

DRAMHammer systematically explores Rowhammer aggression parameters to discover hammering patterns that defeat Target Row Refresh (TRR) on modern DDR4 modules. These patterns are subsequently utilized to locate exploitable bit flips in DRAM and induce bit flips in vulnerable instructions.

## Configuration

The DRAM address mapping functions in `src/Memory/DRAMAddr.cpp` are hardcoded for **Intel Core i7-6700**. For other microarchitectures:

1. Using `../DRAMReverser` provided in the repertory to reverse-engineer the DRAM address functions.
2. Update `load_known_functions()` in `src/Memory/DramAnalyzer.cpp`
3. Fill in the correct mappings in `src/Memory/mat-gen.py`, regenerate, and update matrices in `src/Memory/DRAMAddr.cpp`

## Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```


## Usage

### 1. Fuzzing (Pattern Discovery)

```bash
./DRAMHammer --dimm-id 1 --runtime-limit 21600 --ranks 2 --sweeping
```

| Flag                    | Description                                                  |
| ----------------------- | ------------------------------------------------------------ |
| `--dimm-id 1`           | Arbitrary identifier for logging / output filenames          |
| `--runtime-limit 21600` | Fuzzing duration in seconds                                  |
| `--ranks 2`             | Number of ranks on the target DIMM (affects bank/row mapping) |
| `--sweeping`            | After fuzzing, sweep 256 MB using the best pattern found     |

**Output:**

- `fuzz-summary.json` — All discovered patterns and bit flips during fuzzing
- `sweep-summary-*.json` — Results from the optimal pattern sweep

### 2. Replay (Expanded Scanning)

```bash
./DRAMHammer --dimm-id 1 --runtime-limit 21600 --ranks 2 \
             -y 72624f56-4327-48bb-8b1a-789b06796a88 \
             -j ./fuzz-summary.json \
             -w
```

| Flag        | Description                                     |
| ----------- | ----------------------------------------------- |
| `-y <uuid>` | Pattern ID to replay (from `fuzz-summary.json`) |
| `-j <file>` | Path to the `fuzz-summary.json`                 |
| `-w`        | Enable sweeping mode                            |

## Project Structure

```
├── src/
│   ├── Blacksmith.cpp              # Entry point
│   ├── Forges/
│   │   ├── FuzzyHammerer.cpp       # Fuzzing-based pattern discovery
│   │   ├── ReplayingHammerer.cpp   # Replay known patterns
│   │   └── TraditionalHammerer.cpp # Traditional Rowhammer
│   ├── Fuzzer/                     # Core fuzzing engine
│   │   ├── Aggressor.cpp
│   │   ├── HammeringPattern.cpp
│   │   ├── PatternBuilder.cpp
│   │   └── ...
│   └── Memory/
│       ├── DRAMAddr.cpp            # DRAM address mapping (hardcoded for i7-6700)
│       ├── DramAnalyzer.cpp
│       └── mat-gen.py              # Matrix generator for address mapping
├── include/                        # Headers
├── external/                       # CMake dependencies
└── docker/                         # Docker build environment
```

## Notes

DRAMHammer builds upon Blacksmith and introduces additional attack strategies tailored to the characteristics of ADSs to improve attack effectiveness.





