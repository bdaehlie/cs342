#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

// gcc fork.c -g -o fork

void *PrintThread(void *threadID)
{
   printf("Thread #%ld reporting!\n", (long)threadID);
   pthread_exit(NULL);
}

int
main(int argc, char **argv) {  
  pid_t forkReturn = fork();
  if (forkReturn == -1) {
  	printf("Fork failed!\n");
  }

  bool isParent = (forkReturn != 0);
  if (isParent) {
    printf("Original process!\n");
  } else {
    printf("Second process!\n");
    printf("Second process main thread!\n");

    for (long i = 0; i < 10; i++) {
      pthread_t thread;
      if (pthread_create(&thread, NULL, PrintThread, (void*)i) != 0) {
        printf("Thread creation error!\n");
      }
      pthread_detach(thread);
    }

    pthread_exit(NULL);
  }

  return 0;
}
