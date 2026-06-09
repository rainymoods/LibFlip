# FlipHammer

> A Rowhammer fuzzing framework for discovering TRR-bypassing attack patterns on DDR4 memory, adapted from [Blacksmith](https://github.com/comsec-group/blacksmith) by ETH Zurich.

## Overview

FlipHammer systematically explores Rowhammer aggression parameters to find patterns that defeat Target Row Refresh (TRR) on modern DDR4 modules. After discovering effective patterns, it performs large-scale memory sweeps to locate exploitable bit flips.

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

## Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

**Dependencies:** `g++` (≥ 8), `cmake` (≥ 3.14)


## Usage

### 1. Fuzzing (Pattern Discovery)

```bash
sudo ./FlipHammer --dimm-id 1 --runtime-limit 21600 --ranks 2 --sweeping
```

| Flag                    | Description                                                  |
| ----------------------- | ------------------------------------------------------------ |
| `--dimm-id 1`           | Arbitrary identifier for logging / output filenames          |
| `--runtime-limit 21600` | Fuzzing duration in seconds (6 hours)                        |
| `--ranks 2`             | Number of ranks on the target DIMM (affects bank/row mapping) |
| `--sweeping`            | After fuzzing, sweep 256 MB using the best pattern found     |

**Output:**

- `fuzz-summary.json` — All discovered patterns and bit flips during fuzzing
- `sweep-summary-*.json` — Results from the optimal pattern sweep

### 2. Replay (Expanded Scanning)

```bash
sudo ./FlipHammer --dimm-id 1 --runtime-limit 21600 --ranks 2 \
             -y 4a2d10a4-6a3a-4aba-ba2a-459f0f294ac0 \
             -j ./fuzz-summary.json \
             -w
```

| Flag        | Description                                     |
| ----------- | ----------------------------------------------- |
| `-y <uuid>` | Pattern ID to replay (from `fuzz-summary.json`) |
| `-j <file>` | Path to the `fuzz-summary.json`                 |
| `-w`        | Enable sweeping mode                            |

> To scan beyond the default 256 MB range, modify the memory range in `replay_patterns_brief()` inside `src/Blacksmith.cpp`.

## Hardware Configuration

The DRAM address mapping functions in `src/Memory/DRAMAddr.cpp` are hardcoded for **Intel Core i7-6700**. For other microarchitectures:

1. Reverse-engineer the DRAM address functions (use [DRAMA](https://github.com/IAIK/drama) or [TRResspass' DRAMA](https://github.com/vusec/trrespass/tree/master/drama))
2. Update `load_known_functions()` in `src/Memory/DramAnalyzer.cpp`
3. Fill in the correct mappings in `src/Memory/mat-gen.py`, regenerate, and update matrices in `src/Memory/DRAMAddr.cpp`

## License

MIT License — Copyright (c) 2021 ETH Zurich. See [LICENSE](LICENSE).
