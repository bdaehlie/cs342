#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"
#include "base64.h"

// Compile with: gcc challenge1.c base64.c crypto-utils.c -g -o challenge1

static char* sInputStr = "49276d206b696c6c696e6720796f7572"
                         "20627261696e206c696b65206120706f"
                         "69736f6e6f7573206d757368726f6f6d";

static char* sOutputStr = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBs"
                          "aWtlIGEgcG9pc29ub3VzIG11c2hyb29t";


int main(int argc, char *argv[]) {
  int bytesLen = 0;
  char *bytes = hexStrToBytes(sInputStr, &bytesLen);
  if (!bytes) {
    printf("Failure! Couldn't convert hex to bytes.\n");
    return 1;
  }

  char *base64Str = malloc(Base64encode_len(bytesLen));
  if (!base64Str) {
    printf("Failure! Couldn't alloc buffer for base64 string.\n");
    return 1;
  }
  Base64encode(base64Str, bytes, bytesLen);

  if (strcmp(base64Str, sOutputStr) == 0) {
    printf("Success!\n");
  } else {
    printf("Failure!\n");
  }

  free(base64Str);

  return 0;
}
