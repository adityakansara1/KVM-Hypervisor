# CS695: Topics in Virtualization and Cloud Computing

## Project on KVM-Hypervisor

**Author:** Aditya Hiteshbhai Kansara  
**Roll Number:** 23M0748  
**Date:** 19th February 2024

## Abstract

This report presents the solutions to the assignment on Kernel-based Virtual Machine (KVM) hypervisors, part of the CS695 course on Virtualization and Cloud Computing. The assignment involves building a simple hypervisor, implementing hypercalls, and extending functionality for fractional scheduling of virtual machines.

## Introduction

Virtualization techniques are essential for cloud computing and have evolved significantly to address the challenges posed by complex architectures such as x86. Para and full virtualization techniques do not perform well and do not satisfy the principles of VMM design (Popek & Goldberg) due to the complexity of x86 virtualization. Consequently, hardware vendors now support x86 hardware virtualization natively.

KVM (Kernel-based Virtual Machine) allows the creation of hypervisors in Linux, which can be controlled by userspace programs to run guest VMs while handling x86 hardware virtualization internally. KVM is implemented as a Linux kernel module and exposes a device (`/dev/kvm`) that hypervisors can use to perform operations through `ioctl()` calls.

The KVM API allows userspace hypervisors to perform the following operations:
- Creation of new virtual machines
- Allocation of memory to virtual machines
- Reading and writing virtual CPU registers
- Injecting and interrupting into a virtual CPU
- Running a virtual CPU

## DIY Hypervisor

In this section, we explore the basic implementation of a KVM-based hypervisor. The task involves analyzing and understanding the starter code provided for a simple hypervisor. The goal is to create a flowchart describing the logical steps for setting up and running a virtual machine in long mode using KVM APIs.

### Logical Actions and KVM APIs

1. **Set up the physical memory for the guest OS**
   - **KVM API:** `KVM_SET_USER_MEMORY_REG`
   - **Description:** This ioctl call sets up the memory regions for the guest OS. It specifies the memory regions that the guest will use.

2. **Create a new virtual machine**
   - **KVM API:** `KVM_CREATE_VM`
   - **Description:** This ioctl call creates a new virtual machine instance.

   % Add other actions similarly

## Part 1b: Hypercalls

This part involves extending the simple-kvm hypervisor by implementing various hypercalls. Hypercalls are mechanisms for the guest OS to communicate with the hypervisor. You'll implement hypercalls for printing 32-bit values, counting VM exits, printing strings, and translating guest virtual addresses to host virtual addresses.

### Implemented Hypercalls

- **`void HC_print32bit(uint32_t val)`**
  - **Description:** This hypercall prints a 32-bit value on the terminal.

- **`uint32_t HC_numExits()`**
  - **Description:** This hypercall returns the number of times the guest VM has exited to the hypervisor.

  % Add other hypercalls similarly

## Build the Matrix Cloud

The objective here is to modify the KVM hypervisor to alternate between two virtual machines (VMs) on a single CPU. This part involves modifying the code to ensure that the VMs run one after another, handling VM exits to achieve controlled execution of VMs without using pthreads.

### One at a Time

- **Objective:** Ensure the vCPU threads run on the same core alternatively in a controlled environment.
- **Approach:** Modify the `kvm_run_vm` function to not make any pthread calls but use the main thread to alternate between the two VMs on a `KVM_EXIT_IO`.

### Vulnerabilities Found… Please Fix It

This section addresses the issue of VM scheduling when no I/O operations are occurring. You'll implement a solution using timer interrupts to periodically switch between VMs. This requires setting up a timer and handling signals to ensure fair execution of VMs.

- **Objective:** Achieve control over VM scheduling when no I/O operations are happening.
- **Approach:** Implement timer-based scheduling using the `timer_create()` function to schedule VMs.

### The Final Leap

In the final part, you'll extend the scheduling solution to support fractional scheduling. This involves modifying the hypervisor to allocate 70% of the scheduling time to one VM and 30% to another. The implementation will use macros to define the time quantum and scheduling fractions.

- **Objective:** Implement fractional scheduling to allocate 70% of time to Neo and 30% to Morpheus.
- **Approach:** Define macros `QUANTUM`, `FRAC_A`, and `FRAC_B` for scheduling fractions of time.

## Conclusion

This project demonstrates the practical application of KVM for creating and managing virtual machines, implementing hypercalls, and scheduling VMs. The assignments provide hands-on experience with hypervisor development and virtualization concepts, which are crucial for understanding cloud computing environments.
