# Systems Engineering & Cryptography Implementations

## Overview
This repository contains low-level systems engineering and security tasks, focusing on OS-level packaging and hardware-aware cryptography.

### 1. ALT Linux Package Management (`/alt-linux-packaging`)
* **Objective:** Package the `pushbullet.py` Python library for the ALT Linux Sisyphus repository.
* **Environment:** ALT Linux (ARM64 VM), utilizing `rpm-build` and custom `.rpmmacros`.
* **Details:** Includes the `.spec` file configured with modern ALT Linux RPM macros (`%pyproject_build`, `%pyproject_install`) to ensure proper dependency resolution and package generation via `rpmbuild`.

### 2. Hardware-Aware Cryptography (`/elbrus-crypto-c`)
* **Objective:** Establish a baseline C implementation of the ChaCha20 stream cipher.
* **Details:** This code is intentionally written without standard software optimizations (like manual loop unrolling or vectorization). It serves as a testing baseline to observe compile-time vs. runtime optimization differences between x86 processors and the Elbrus (E2K) architecture.

---

## Technical Notes: Migrating to Modern Python Packaging Standards

During the build process for `pushbullet.py`, the system threw warnings regarding deprecated RPM macros. 

**The Warning:**
```text
WARNING: %python3_build is deprecated and will be removed in future, please use %pyproject_build instead
WARNING: %python3_install is deprecated and will be removed in future, please use %pyproject_install instead



            I updated the .spec file to comply with modern ALT Linux Python packaging standards:

            Build Dependencies: Added rpm-build-pyproject to the BuildRequires list.

            Macros: Swapped the legacy commands for %pyproject_build and %pyproject_install.

            Metadata Update: Because modern pyproject builds generate .dist-info directories instead of legacy .egg-info directories, the initial build failed with a File not found by glob error. I resolved this by updating the %files section to target %python3_sitelibdir/*dist-info/ instead of %python3_sitelibdir/pushbullet.py-*.egg-info/.

          This modernization successfully compiled both the .rpm and .src.rpm files!