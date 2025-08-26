file(REMOVE_RECURSE
  "lib/libopenblas.pdb"
  "lib/libopenblas.so"
  "lib/libopenblas.so.0"
  "lib/libopenblas.so.0.3"
)

# Per-language clean rules from dependency scanning.
foreach(lang ASM C Fortran)
  include(CMakeFiles/openblas_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
