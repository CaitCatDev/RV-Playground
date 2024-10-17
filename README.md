# RISC-V VF2 Playground
This repo serves as a backup of my "playground" code for RISC-V I would no recommend using this code on real hardware it should work on a Visionfive 2 Revesion 1.3b board at least.

## How to build
To build see below. Make sure to call `make clean` when building for a different platform as some code files need to be regenerated with new arguments.
```sh
make CFLAGS="-DVIRTUAL_RISCV" #To build for virtual QEMU platform
make vf2.bin CFLAGS="-DVF2_RISCV" #To build for Visionfive 2
```

## Bug Reporting
This is code that makes lots of assumptions and is likely to have very obvious bugs but feel free to file a github issues report


