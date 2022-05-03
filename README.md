# os-from-scratch
An operating system with x86 CPU architecture written from scratch.

## Requirements
* NASM
* GNU C/C++ Compiler

## How to Build Image

```
# Clean up generated files
make clean

# Generate OS image
make all
```

Run OS image using an Emulator:
```
qemu-system-i386 -fda os-image.bin
```

* Screen :heavy_check_mark:
* Keyboard :heavy_check_mark:
* Interrupts (IDT and IRQs) :heavy_check_mark:
* Timer :heavy_check_mark:
* Paging :clock9:






## References
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
