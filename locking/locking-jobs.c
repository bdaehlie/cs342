#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

// gcc -pthread -g -o locking-jobs locking-jobs.c

// Tips
//
// You can direct output from this program to a file like this:
//
// $ ./locking-jobs > output.txt
//
// Then you can look for duplicate lines in the file like this:
//
// $ cat output.txt | uniq -d
//
// Alternatively you can skip the file and just pipe to uniq:
//
// $ ./locking-jobs | uniq -d

#define JOB_COUNT 1000000

uint64_t jobs_completed = 0;

void do_job(uint64_t job_id) {
  for (int i = 0; i < 5; i++) {
    asm("nop");
  }
  printf("Completed job #%lld\n", job_id);
}

void *do_jobs(void *thread_id)
{
  printf("Thread #%p reporting for duty!\n", thread_id);

  while (jobs_completed < JOB_COUNT) {
    do_job(jobs_completed + 1);
    jobs_completed++;
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  for (long i = 0; i < 2; i++) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, do_jobs, (void*)i) != 0) {
      printf("Thread creation error!\n");
    }
    pthread_detach(thread);
  }

  pthread_exit(NULL);

  return 0;
}
