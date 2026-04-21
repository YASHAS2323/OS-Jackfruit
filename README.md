# Multi-Container Runtime

TEAM MEMBERS
VISHRUTA - PES1UG24CS538
YASHAS C - PES1UG24CS544

A lightweight Linux container runtime in C with a long-running supervisor and a kernel-space memory monitor.

Read [`project-guide.md`](project-guide.md) for the full project specification.

---

## Getting Started

### 1. Fork the Repository

1. Go to [github.com/shivangjhalani/OS-Jackfruit](https://github.com/shivangjhalani/OS-Jackfruit)
2. Click **Fork** (top-right)
3. Clone your fork:

```bash
git clone https://github.com/<your-username>/OS-Jackfruit.git
cd OS-Jackfruit
```

### 2. Set Up Your VM

You need an **Ubuntu 22.04 or 24.04** VM with **Secure Boot OFF**. WSL will not work.

Install dependencies:

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
```

### 3. Run the Environment Check

```bash
cd boilerplate
chmod +x environment-check.sh
sudo ./environment-check.sh
```

Fix any issues reported before moving on.

### 4. Prepare the Root Filesystem

```bash
mkdir rootfs-base
wget https://dl-cdn.alpinelinux.org/alpine/v3.20/releases/x86_64/alpine-minirootfs-3.20.3-x86_64.tar.gz
tar -xzf alpine-minirootfs-3.20.3-x86_64.tar.gz -C rootfs-base

# Make one writable copy per container you plan to run
cp -a ./rootfs-base ./rootfs-alpha
cp -a ./rootfs-base ./rootfs-beta
```

Do not commit `rootfs-base/` or `rootfs-*` directories to your repository.

### 5. Understand the Boilerplate

The `boilerplate/` folder contains starter files:

| File                   | Purpose                                             |
| ---------------------- | --------------------------------------------------- |
| `engine.c`             | User-space runtime and supervisor skeleton          |
| `monitor.c`            | Kernel module skeleton                              |
| `monitor_ioctl.h`      | Shared ioctl command definitions                    |
| `Makefile`             | Build targets for both user-space and kernel module |
| `cpu_hog.c`            | CPU-bound test workload                             |
| `io_pulse.c`           | I/O-bound test workload                             |
| `memory_hog.c`         | Memory-consuming test workload                      |
| `environment-check.sh` | VM environment preflight check                      |

Use these as your starting point. You are free to restructure the repository however you want — the submission requirements are listed in the project guide.

### 6. Build and Verify

```bash
cd boilerplate
make
```

If this compiles without errors, your environment is ready.

### 7. GitHub Actions Smoke Check

Your fork will inherit a minimal GitHub Actions workflow from this repository.

That workflow only performs CI-safe checks:

- `make -C boilerplate ci`
- user-space binary compilation (`engine`, `memory_hog`, `cpu_hog`, `io_pulse`)
- `./boilerplate/engine` with no arguments must print usage and exit with a non-zero status

The CI-safe build command is:

```bash
make -C boilerplate ci
```

This smoke check does not test kernel-module loading, supervisor runtime behavior, or container execution.

---

## What to Do Next

Read [`project-guide.md`](project-guide.md) end to end. It contains:

- The six implementation tasks (multi-container runtime, CLI, logging, kernel monitor, scheduling experiments, cleanup)
- The engineering analysis you must write
- The exact submission requirements, including what your `README.md` must contain (screenshots, analysis, design decisions)

Your fork's `README.md` should be replaced with your own project documentation as described in the submission package section of the project guide. (As in get rid of all the above content and replace with your README.md)

Evaluation & Screenshots
Part A: User-Space Execution
1. Multi-Container Supervision

Description: Evidence of the supervisor managing multiple independent containers simultaneously.

   
<img width="744" height="196" alt="supervision" src="https://github.com/user-attachments/assets/92b5e553-ef99-49b4-8fbf-96565361e2c7" />




2. Metadata Tracking

Description: Output of the ps command showing tracked PIDs, states, and memory limits.

   <img width="744" height="196" alt="metadataTracking" src="https://github.com/user-attachments/assets/d5723ec3-d19b-4492-bea4-9d52d078b57e" />



3. Bounded-Buffer Logging

Description: Evidence of the logging pipeline capturing output from a containerized process.

   <img width="742" height="139" alt="logPiping" src="https://github.com/user-attachments/assets/bcd9abc6-2bee-4282-a186-7ab6d828902f" />

   <img width="660" height="200" alt="image" src="https://github.com/user-attachments/assets/e13f8b11-7886-4089-a4ba-426dcbf95d7f" />


4. CLI and IPC

Description: Demonstration of the CLI sending a command and receiving a synchronous response from the supervisor via UNIX socket.

   <img width="746" height="192" alt="Screenshot from 2026-04-16 13-21-55" src="https://github.com/user-attachments/assets/3657ddb4-7d46-4ed3-89f2-80373d4e0a61" />



Part B: Kernel & Resource Management
5. Soft-Limit Warning

Description: Kernel ring buffer (dmesg) output showing the SOFT LIMIT warning when a container exceeds its initial threshold.
<img width="742" height="139" alt="soflimit" src="https://github.com/user-attachments/assets/21734a18-7f5a-415c-b8eb-b766f4ae07cb" />



6. Hard-Limit Enforcement

Description: Evidence of the kernel module sending SIGKILL to a container and the supervisor updating its state to killed.

<img width="742" height="139" alt="hardlimit" src="https://github.com/user-attachments/assets/5f6bfeef-a9cc-4bff-ba8e-269497e14f05" />





7. Scheduling Experiment

Description: top output showing the impact of the --nice flag on CPU share between a normal and a low-priority container.

   <img width="1145" height="464" alt="priorityContainer" src="https://github.com/user-attachments/assets/394eaba0-d88d-4431-886e-3c59f6bd0db4" />




8. Clean Teardown

Description: Evidence of a clean exit: no zombie processes in ps aux and successful rmmod of the kernel module.
<img width="1145" height="281" alt="cleanTeardown" src="https://github.com/user-attachments/assets/365224e7-c4fa-438f-a5e9-6b569e7c9509" />


How to Build and Run

    Compile the project:
    Bash

    make

    Load the Monitor:
    Bash

    sudo insmod monitor.ko
    
<img width="746" height="63" alt="insmod" src="https://github.com/user-attachments/assets/62950223-6884-4caf-bc26-dcad3325b6b8" />



    

    Start the Supervisor:
    Bash

    sudo ./engine supervisor ./rootfs-base

    Run a Container:
    Bash

    sudo ./engine start <id> ./rootfs-base <command>
