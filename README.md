## Multilevel Feedback Scheduling Algorithm Implementation

This project implements a Multilevel Feedback Scheduling Algorithm in C. The algorithm efficiently manages multiple processes with varying arrival times and execution requirements.

### Features:
- **Instruction Interpretation**: The system scans program files, interprets instructions, and stores them in memory for later execution.
- **Process Initialization**: Processes are initialized upon arrival, and corresponding Process Control Blocks (PCBs) are created.
- **Instruction Execution**: Instructions are accessed from memory using their own program counter that is present in the PCB and then executed, ensuring correct interpretation and operation execution.
- **Mutex Handling**: Mutexes provide synchronization for critical resources, preventing race conditions.
- **Dynamic Priority Adjustment**: Process priorities are dynamically adjusted based on execution performance.
- **State Management**: Processes transition between different states (Ready, Running, Blocked, and Finished) as per their execution status.
