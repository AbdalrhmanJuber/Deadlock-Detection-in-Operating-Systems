# Deadlock Detection in Operating Systems

## Project Overview
This project involves detecting deadlocks in a system with multiple processes and resources. It reads data from CSV files representing resource allocation, requests, and available resources, then determines if a deadlock condition exists.

## Project Objectives
- Implement a deadlock detection algorithm.
- Read and process data from input files (CSV format).
- Determine if a deadlock exists and identify the involved processes.
- Provide a sequence of process executions if no deadlock occurs.

## Input Data
- `Allocation.csv`: NxM allocation matrix.
- `Request.csv`: NxM request matrix.
- `Available.csv`: M available resource vector.

## Key Functionalities
### 1. File Processing
- Reads allocation, request, and available resource data from CSV files.
- Validates data dimensions for consistency.

### 2. Deadlock Detection Algorithm
- Implements logic to check if processes' requests can be satisfied with available resources.
- Identifies processes involved in a deadlock, if any.

### 3. Output Generation
- Clearly indicates if a deadlock occurred.
- Lists the processes involved or provides a safe execution sequence.

## Execution
- Compilation:
```bash
gcc 1211769_Task3.c -o DeadlockDetection
```
- Run the program:
```bash
./DeadlockDetection
```

## Sample Output
- **Deadlock Case:**
```
Deadlock occurred on processes: P1, P2, P3...
```

- **No Deadlock Case:**
```
No Deadlock occurred. Possible execution order: P4, P8, P9...
```

## Technologies Used
- C Programming Language
- CSV File Processing

## University
Birzeit University, Faculty of Engineering and Technology, Department of Electrical and Computer Engineering.

## Date
January 28, 2024
