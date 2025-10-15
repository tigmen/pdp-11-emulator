#include "config.h"
#include <assert.h>

void b_write(address adr, byte src) {
        mem[adr] = src;
}

byte b_read(address adr) {
        return mem[adr];
}

void w_write(address adr, word src) {
	assert(adr&1);

	mem[adr] = src & BYTEMASK;
	src >>= BYTESIZE;
	mem[adr + 1] src & BYTEMASK;
}

word w_read(address adr) {
	assert(adr&1);

        word w = mem[adr + 1];
        w <<= BYTESIZE;
        w |= mem[adr];

        return w & WORDMASK;
}

	
