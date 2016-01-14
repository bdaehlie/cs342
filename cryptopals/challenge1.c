#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Compile with: gcc challenge1.c -g -o challenge1

static char* sInputStr = "49276d206b696c6c696e6720796f7572"
                         "20627261696e206c696b65206120706f"
                         "69736f6e6f7573206d757368726f6f6d";

static char* sOutputStr = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBs"
                          "aWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

short hexCharToByte(char aHexChar) {
  if (aHexChar >= 48 && aHexChar <= 58) {
    return aHexChar - 48;
  }
  if (aHexChar >= 97 && aHexChar <= 122) {
    return aHexChar - 87;
  }
  printf("Failure! Invalid hex character.\n");
  exit(1);
}

// returns a malloc'd byte buffer, caller frees
unsigned short* hexStrToBytes(char* aHexStr, unsigned int* aOutLen) {
  // need valid input
  if (!aHexStr) {
    return NULL;
  }

  // need an even number of hex digits to convert to bytes
  if (strlen(aHexStr) % 2 != 0) {
    return NULL;
  }

  // calculate the length of the output buffer
  *aOutLen = strlen(aHexStr) / 2;
  if (*aOutLen == 0) {
    return NULL;
  }

  // create output buffer
  unsigned short *outBuf = malloc(*aOutLen);
  if (!outBuf) {
    return NULL;
  }

  // fill the output buffer
  unsigned int inputLen = strlen(aHexStr);
  for (unsigned int i = 0; i < inputLen; i = i + 2) {
    char char1 = aHexStr[i];
    char char2 = aHexStr[i + 1];

    unsigned short byte = 0;

    byte = hexCharToByte(char1) << 4;
    byte = byte | hexCharToByte(char2);

    outBuf[i / 2] = byte;
  }

  return outBuf;
}

char* bytesToB64Str(unsigned short* aInput) {
  return NULL;
}

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

