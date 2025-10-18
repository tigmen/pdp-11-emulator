#include <assert.h>
#include "config.h"

char X[] = "0123456789abcdef";
uint16_t x_read_uint16(FILE* stream) {
	uint16_t result = 0;

	char c = fgetc(stream);
	char* pc = strchr(X, c);
	/* while(!(pc) && pc != NULL) { */
	/*	c = fgetc(stream); */
	/* } */
	while (pc = strchr(X, c)) {
		result *= 16;
		result += (pc - X);
		c = fgetc(stream);
	}

	return result;
}

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

void load_file(char* path) {
	FILE* script = fopen(path, "r");
	if (script == NULL) {
		perror("\033[1;31mNo script file\033[0m");
		exit(1);
	}

	char buf;
	while ((buf = fgetc(script)) != EOF) {
		fseek(script, -1, SEEK_CUR);

		address adr = x_read_uint16(script);
		address n = x_read_uint16(script);

		for (address i = 0; i < n; i++) {
			byte input = x_read_uint16(script);
			b_write(adr + i, input);
		}
	}

	fclose(script);
	return;
}
