#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);

  printf("User CPU time used: %ld.%06ld seconds\n",
    usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
  printf("System CPU time used: %ld.%06ld seconds\n",
    usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
  printf("Maximum resident set size: %ld kilobytes\n", usage.ru_maxrss);
  printf("Integral shared memory size: %ld kilobytes\n", usage.ru_ixrss);
  printf("Integral unshared data size: %ld kilobytes\n", usage.ru_idrss);
  printf("Integral unshared stack size: %ld kilobytes\n", usage.ru_isrss);
  printf("Page reclaims (soft page faults): %ld\n", usage.ru_minflt);
  printf("Page faults (hard page faults): %ld\n", usage.ru_majflt);
  printf("Swaps: %ld\n", usage.ru_nswap);
  printf("Block input operations: %ld\n", usage.ru_inblock);
  printf("Block output operations: %ld\n", usage.ru_oublock);
  printf("IPC messages sent: %ld\n", usage.ru_msgsnd);
  printf("IPC messages received: %ld\n", usage.ru_msgrcv);
  printf("Signals received: %ld\n", usage.ru_nsignals);
  printf("Voluntary context switches: %ld\n", usage.ru_nvcsw);
  printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);

  return 0;
}