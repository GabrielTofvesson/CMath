#ifndef VARINT_H
#define VARINT_H

#include "bits.h"

typedef char * varint;

varint varint_encode(unsigned long long);
unsigned long long varint_decode(varint);
unsigned long long zigzag_encode(long long);
long long zigzag_decode(unsigned long long);

#endif
