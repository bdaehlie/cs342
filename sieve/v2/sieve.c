#include <stdio.h>
#include <string.h>

#define PRIME 1
#define NOT_PRIME 0

static int max = 1000;

// gcc sieve.c -g -o sieve

int
main(int argc, char **argv)
{
  char prime_map[max];

  memset(prime_map, PRIME, max);

  for (int i = 2; i < max; i++) {
    if (prime_map[i] == PRIME) {
      printf("%d\n", i);
      for (int j = i; j < max; j += i) {
        prime_map[j] = NOT_PRIME;
      }
    }
  }

  return 0;
}
