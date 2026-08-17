## Goal

DRAMReverser aims to reverse-engineer the DRAM mapping functions.

## Notes

This DRAMReverser is built upon the [DRAMA](https://github.com/vusec/trrespass/tree/master/drama) module of [TRResspass](https://github.com/vusec/trrespass/tree/master).

## Usage

```
./test [-h] [-s sets] [-r rounds] [-t threshold] [-o o_file] [-v] [--mem mem_size]
          -h                     = this help message
          -s sets                = number of expected sets            (default: 32)
          -r rounds              = number of rounds per tuple         (default: 1000)
          -t threshold           = time threshold for conflicts       (default: 340)
          -o o_file              = output file for mem profiling      (default: access.csv)
          --mem mem_size         = allocation size                    (default: 5368709120)
          -v                     = verbose
```

**Number of sets:**

- The number of expected sets is defined by the memory configuration. For instance in a common dual-rank, single-channel configuration you would expect 32 banks (i.e., sets) in total. You can pass any value you want to the script. If this value is unknown 16 is usually a safe bet.

**Time threshold:**

- You can identify the time threshold by running the tool the first time with `-o` and plotting the results with the histogram.py script available in the repo. Once you know the threshold you can dynamically pass it to the binary.