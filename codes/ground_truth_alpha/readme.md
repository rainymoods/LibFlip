# 代码说明
本工具的作用是翻转cblas_sgemm以及sgemm_xx函数

比特翻转的核心代码存储在```llvm-pass/flipBranches```和```llvm-pass/flipLauncher```中

# 本地运行说明
替换同目录Makefile：将XXXX替换为自己的路径

将```openblas_makefiles/attack/interface/Makefile``` ```openblas_makefiles/attack/driver/level3/Makefile```中的XXXX替换为自己的路径

随后，在同目录下执行make ground_truth即可进行翻转
