#pragma once
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word address;

void b_write(address, byte);
byte b_read(address);
void w_write(address, word);
word w_read(address);
