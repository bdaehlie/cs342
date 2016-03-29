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

#define THREAD_COUNT 2

int64_t jobs_available = 1000000;

void do_job(uint64_t job_id) {
  for (int i = 0; i < 5; i++) {
    asm("nop");
  }
  printf("Completed job #%lld\n", job_id);
}

void *do_jobs(void *thread_id)
{
  int64_t current_job = 0;
  while (true) {
    current_job = jobs_available;
    if (current_job < 1) {
      break;
    }
    jobs_available--;

    do_job(current_job);
  }

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  pthread_t threads[THREAD_COUNT];
  for (int i = 0; i < THREAD_COUNT; i++) {
    if (pthread_create(&threads[i], NULL, do_jobs, (void*)(long)i) != 0) {
      printf("Thread creation error!\n");
    }
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
