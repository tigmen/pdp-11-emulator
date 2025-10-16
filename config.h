#pragma once

#include <inttypes.h>

#define PRIbyte PRIu8
#define PRIword PRIu16
#define PRIadr PRIword

#define BYTEMASK 0xFF
#define BYTESIZE 8
#define WORDMASK 0xFFFF
#define WORDSIZE 16

typedef uint8_t byte;
typedef uint16_t word;
typedef word address;

extern byte mem[(address)(-1)];

void b_write(address, byte);
byte b_read(address);
void w_write(address, word);
word w_read(address);

void load_file(char*);
void print_segment(address, int);
