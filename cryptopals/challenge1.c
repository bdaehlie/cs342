#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

// Compile with: gcc challenge1.c -g -o challenge1

static char* sInputStr = "49276d206b696c6c696e6720796f7572"
                         "20627261696e206c696b65206120706f"
                         "69736f6e6f7573206d757368726f6f6d";

static char* sOutputStr = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBs"
                          "aWtlIGEgcG9pc29ub3VzIG11c2hyb29t";


int main(int argc, char *argv[]) {
  unsigned int outLen = 0;
  unsigned short *bytes = hexStrToBytes(sInputStr, &outLen);
  if (!bytes) {
    printf("Failure! Couldn't convert hex to bytes.\n");
    return 1;
  }

  char *b64Str = bytesToB64Str(bytes);
  if (!b64Str) {
    printf("Failure! Couldn't convert bytes to base64.\n");
    return 1;
  }

  if (strcmp(b64Str, sOutputStr) == 0) {
    printf("Success!\n");
  } else {
    printf("Failure!\n");
  }

  return 0;
}

