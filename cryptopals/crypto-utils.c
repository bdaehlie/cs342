#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto-utils.h"

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
