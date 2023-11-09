#include "dbg.h"

typedef unsigned char byte;

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte_)  \
  ((byte_) & 0x80 ? '1' : '0'), \
  ((byte_) & 0x40 ? '1' : '0'), \
  ((byte_) & 0x20 ? '1' : '0'), \
  ((byte_) & 0x10 ? '1' : '0'), \
  ((byte_) & 0x08 ? '1' : '0'), \
  ((byte_) & 0x04 ? '1' : '0'), \
  ((byte_) & 0x02 ? '1' : '0'), \
  ((byte_) & 0x01 ? '1' : '0') 

void p(void *base, size_t nmemb, size_t size)
{
    for (size_t i = 0; i < nmemb; i++) {
        byte *elem = (byte*)base + size * i;
        for (size_t k = size; k > 0; k--) {
            printf(BYTE_TO_BINARY_PATTERN " ", BYTE_TO_BINARY(*(elem + k - 1)));
        }
        printf("\n");
    }
}
