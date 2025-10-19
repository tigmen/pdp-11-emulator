#include <assert.h>
#include "config.h"

void b_write(address adr, byte src) {
	mem[adr] = src & BYTEMASK;
}

byte b_read(address adr) {
	return mem[adr];
}

void w_write(address adr, word src) {
	assert(~adr & 1);

	b_write(adr, src & BYTEMASK);
	src >>= BYTESIZE;
	b_write(adr + 1, src & BYTEMASK);
}

word w_read(address adr) {
	assert(~adr & 1);

	word w = b_read(adr + 1);
	w <<= BYTESIZE;
	w |= b_read(adr);

	return w & WORDMASK;
}

char X[] = "0123456789abcdef";
address toAddress(char* src) {
	char* p = src;
	address result = 0;

	while (*p++) {
		result *= 16;
		result += (strchr(X, p[-1]) - X);
	}

	return result;
}
byte toByte(char* src) {
	char* p = src;
	byte result = 0;

	while (*p++) {
		result *= 16;
		result += (strchr(X, p[-1]) - X);
	}

	return result;
}

void load_file(FILE* script) {
	if (script == NULL) {
		perror("\033[1;31mNo script file\033[0m");
		exit(1);
	}

	char input[WORD2POWER + 1];
	while (fgets(input, sizeof(input), script)) {
		fgetc(script);
		address adr = toAddress(input);

		fgets(input, sizeof(input), script);
		fgetc(script);
		address n = toAddress(input);

		char x[BYTE2POWER + 1];
		for (unsigned i = 0; i < n; i++) {
			fgets(x, sizeof(x), script);
			fgetc(script);
			b_write(adr + i, toByte(x));
		}
	}

	return;
}

void print_segment(address adr, address n) {
	for(int i = 0; i < n; i+=2) {
		word line = w_read(adr + i);
		printf("%06o: %06o %04x\n", adr + i, line, line);
	}

	return;
}
