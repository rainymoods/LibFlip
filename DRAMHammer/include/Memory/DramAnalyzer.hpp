/*
 * Copyright (c) 2021 by ETH Zurich.
 * Licensed under the MIT License, see LICENSE file for more details.
 */

#ifndef DRAMANALYZER
#define DRAMANALYZER

#include <cinttypes>
#include <vector>
#include <random>

#include "Utilities/AsmPrimitives.hpp"

class DramAnalyzer {
 private:
  std::vector<std::vector<volatile char *>> banks;

  std::vector<uint64_t> bank_rank_functions;

  uint64_t row_function;

  volatile char *start_address;

  void find_targets(std::vector<volatile char *> &target_bank);

  std::mt19937 gen;

  std::uniform_int_distribution<int> dist;

 public:
  explicit DramAnalyzer(volatile char *target);

  /// Finds addresses of the same bank causing bank conflicts when accessed sequentially
  void find_bank_conflicts();

  /// Measures the time between accessing two addresses.
  // static int inline measure_time(volatile char *a1, volatile char *a2) {
  //   uint64_t before, after;
  //   before = rdtscp();
  //   lfence();
  //   for (size_t i = 0; i < DRAMA_ROUNDS; i++) {
  //     (void)*a1;
  //     (void)*a2;
  //     clflushopt(a1);
  //     clflushopt(a2);
  //     mfence();
  //   }
  //   after = rdtscp();
  //   return (int) ((after - before)/DRAMA_ROUNDS);
  // }

  static int gt(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
  }
  
  uint64_t median(uint64_t* vals, size_t size) {
    qsort(vals, size, sizeof(uint64_t), gt);
    return ((size % 2) == 0) ? vals[size / 2] : (vals[(size_t)size / 2] + vals[((size_t)size / 2 + 1)]) / 2;
  }
  
  uint64_t measure_time(volatile char* a1, volatile char* a2, size_t rounds = 1000) {

    uint64_t* time_vals = (uint64_t*)calloc(rounds, sizeof(uint64_t));
    uint64_t t0;
    sched_yield();
    for (size_t i = 0; i < rounds; i++) {
      mfence();
      t0 = rdtscp();
      *a1;
      *a2;
      time_vals[i] = rdtscp() - t0;
      lfence();
      clflush(a1);
      clflush(a2);

    }

    uint64_t mdn = median(time_vals, rounds);
    free(time_vals);
    return mdn;
  }
  
  std::vector<uint64_t> get_bank_rank_functions();

  void load_known_functions(int num_ranks);

  /// Determine the number of possible activations within a refresh interval.
  size_t count_acts_per_trefi();
};

#endif /* DRAMANALYZER */
