# Operating Systems (202.1.3031) – Assignment 1: Processes and Scheduling

This repository contains my solution for **Assignment 1** of the Operating Systems course.  
It is based on **xv6-riscv** and extends the kernel and user space with new system calls and programs related to processes and scheduling.

---

## Implemented Features
- **Hello World Program** – added `helloworld.c`, which prints `"Hello World xv6"`.  
- **memsize() System Call** – returns the memory size of the calling process. Verified using `memsize_test.c`.  
- **Exit Messages** – extended `exit` and `wait` to support exit messages. Implemented `goodbye.c` and modified `sh.c` to show the message after process termination.  
- **Work Distribution** – implemented new system calls `forkn` and `waitall` to manage multiple child processes. Wrote `bigarray.c` to parallelize array summation across several processes.  

---

## Skills Gained
- Extending xv6 with new system calls.  
- Working with process creation (`fork`) and scheduling.  
- Managing memory size reporting in the OS kernel.  
- Implementing parent/child process synchronization (`wait`, `waitall`).  
- Writing and testing user-level programs in xv6.  

---

## ▶️ How to Run
Build and run xv6:
```bash
make qemu

Inside xv6 shell:

helloworld
memsize_test
goodbye
bigarray
