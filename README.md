# turbo-octo-waddle

## How to use thread-limit c program

program that determine the maximum possible count of thread creation

source: https://askubuntu.com/questions/845380/bash-fork-retry-resource-temporarily-unavailable

compile with:   gcc -pthread -o thread-limit thread-limit.c

## getrusage

**Note that the values returned by getrusage are platform-specific!!!**

In C, there is no standard way to get the current memory usage of a program. However, there are platform-specific APIs and libraries that can be used to get this information.

For example, on Linux systems, you can use the getrusage function to get information about the resource usage of the calling process or one of its child processes. getrusage returns a structure that contains information about the CPU time used by the process and the maximum size of its data segment, among other things.



Example Code gets the size of the process's memory (maximum resident set size) that is held in RAM.
```
struct rusage usage;
int result = getrusage(RUSAGE_SELF, &usage);
if (result == -1) {
perror("getrusage");
return 1;
}

printf("Max resident set size: %ld\n", usage.ru_maxrss);
```

The information retrieved by getrusage includes:

1. User time: The amount of CPU time spent executing code in user mode (i.e., outside of the kernel).
2. System time: The amount of CPU time spent executing code in the kernel on behalf of the process.
3. Maximum resident set size: The maximum amount of physical memory used by the process.
4. Integral shared memory size: The amount of shared memory used by the process.
5. Integral unshared memory size: The amount of unshared memory used by the process.
6. Page reclaims: The number of page faults serviced without any I/O.
7. Page faults: The number of page faults serviced that required I/O.
8. Swaps: The number of times the process was swapped out of main memory.
9. Input operations: The number of read operations performed by the process.
10. Output operations: The number of write operations performed by the process.
11. Context switches: The number of times the process was context-switched involuntarily (i.e., without requesting it).
12. Block input operations: The number of input operations blocked (i.e., waiting for data to become available).
13. Block output operations: The number of output operations that blocked.
