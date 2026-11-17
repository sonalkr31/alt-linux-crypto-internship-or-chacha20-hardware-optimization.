# Information Security Internship: Cryptography & Secure Packaging

A portfolio repository showcasing the technical deliverables from my Information Security internship (October – November 2026), specializing in **Trusted Software and Hardware for Critical Information Infrastructure**. 

This project demonstrates practical experience bridging DevSecOps, low-level systems engineering, and hardware-specific performance optimization.

## 📋 Project Overview

During this internship, I successfully completed two primary technical tracks:

1. **Low-Level Cryptography & Hardware Optimization:** Designed and engineered a custom, hardware-optimized implementation of the ChaCha20 stream cipher in C. 
2. **Secure Linux Packaging & Reproducible Builds:** Ported and packaged a Python library for ALT Linux (targeting Elbrus processors) using secure, isolated build environments.

---

## 🔐 Track 1: ChaCha20 Hardware Optimization (C)

To maximize execution speed for cryptographic operations, I wrote a C-based implementation of the ChaCha20 cipher that intentionally bypasses standard RAM arrays. By unpacking state matrices directly into local variables, the compiler is forced to load the data into ultra-fast hardware CPU registers. 

### Key Techniques Used:
* **Register Allocation:** Eliminated memory-bound array lookups.
* **Loop Unrolling:** Used C preprocessor macros (`#define`) to paste ARX (Add-Rotate-XOR) operations directly into the execution path, stripping away function-call overhead.
* **Compiler Interaction:** Profiled and benchmarked execution using maximum compiler optimizations (`gcc -O3`) over a 32GB data payload (500 million blocks).

### How to Run the Benchmark
You can run the benchmarking tool on any Linux/macOS terminal with GCC installed. It compares the execution time of the standard array-based implementation against the optimized register-based implementation.

1. **Compile the benchmark (without auto-optimization to see manual architectural gains):**
   ```bash
   gcc compare.c -o benchmark_raw
   ./benchmark_raw
