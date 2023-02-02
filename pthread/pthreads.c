#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/sysinfo.h>


#define MAX_THREADS 100000
#define PTHREAD_STACK_MIN 1*1024*1024*1024
int i;



void run(void) {
  //std::cout << "Thread ID: " << pthread_self() << std::endl;
  FILE *fp;
  fp = fopen("/sys/fs/cgroup/pids/user.slice/user-0.slice/pids.current", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
  }
  int pid_count;
  fscanf(fp, "%d", &pid_count);
  printf("The current number of processes is: %d\n", pid_count);
  fclose(fp);
  sleep(60 * 60);
}

int main(int argc, char *argv[]) {
  int rc = 0;
  pthread_t thread[MAX_THREADS];
  pthread_attr_t thread_attr;
  int nprocs = get_nprocs();
  pthread_attr_init(&thread_attr);
  pthread_attr_setstacksize(&thread_attr, PTHREAD_STACK_MIN);

  printf("Creating threads ...\n");
  for (i = 0; i < MAX_THREADS && rc == 0; i++) {
    rc = pthread_create(&(thread[i]), &thread_attr, (void *) &run, NULL);
    nprocs = get_nprocs();
    if (rc == 0) {
      pthread_detach(thread[i]);
      //printf("Thread %i created with PID %lu\n", i + 1, (unsigned long) pthread_self());
      if ((i + 1) % 100 == 0)
        printf("%i threads with nprocs: %d so far ...\n", i + 1, nprocs);
    } else {
      printf("Failed with return code %i creating thread %i nprocs: %d (%s).\n",
         rc, i + 1,nprocs , strerror(rc));

      // can we allocate memory?
      char *block = NULL;
      block = malloc(65545); // default maximum PID number, which is 32768
                             // Note that is quite on purpose that a number bigger than 2**16 was chosen, to see if it was actually allowed.
      if(block == NULL)
        printf("Malloc failed too :( \n");
      else
        printf("Malloc worked, hmmm\n");
    }
  }
sleep(60*60); // ctrl+c to exit; makes it easier to see mem use
  exit(0);
}
