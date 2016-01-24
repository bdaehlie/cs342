#include <stdio.h>
#define N 1000

// gcc sieve.c -g -o sieve

int
main(int argc, char **argv)
{
  char is_prime[N];
  int i, j;
  for (i = 0; i < N; i++) {
    is_prime[i] = 1;
  }
  for (i = 2; i < N; i++) {
    if (is_prime[i]) { 
      printf("%d\n", i);
      for (j = i; j < N; j += i) {
        is_prime[j] = 0;
      }
    }
  }
  return 0;
}
