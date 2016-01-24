#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PRIME 1
#define NOT_PRIME 0

// gcc sieve.c -g -o sieve

static int
parse_max(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s max_prime\n", argv[0]);
    return -1;
  }

  errno = 0;

  int max = atoi(argv[1]);
  if (errno != 0 || max == 0) {
    fprintf(stderr, "Invalid integer for max_prime: %s\n", argv[1]);
    return -1;
  }

  return max;
}

static void
run_sieve(int max, char *prime_map)
{
  memset(prime_map, PRIME, max);

  for (int i = 2; i < max; i++) {
    if (prime_map[i] == PRIME) {
      printf("%d\n", i);
      for (int j = i; j < max; j += i) {
        prime_map[j] = NOT_PRIME;
      }
    }
  }
}

int
main(int argc, char **argv)
{
  int max = parse_max(argc, argv);
  if (max < 0) {
    return 1;
  }

  char* prime_map = malloc(max);
  if (!prime_map) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
  }

  run_sieve(max, prime_map);

  free(prime_map);

  return 0;
}
