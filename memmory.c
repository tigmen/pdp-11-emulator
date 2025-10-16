#include <assert.h>
#include <stdlib.h>
#include "config.h"

void b_write(address adr, byte src) {
        mem[adr] = src;
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

        address adr;
        address n;
        while (fscanf(script, "%" PRIadr "%d" PRIadr, &adr, &n) == 2) {
                for (int i = 0; i < n; i++) {
                        byte input;
                        fscanf(script, "%o", &input);
                        b_write(adr + i, input);
                }
        }

        fclose(script);
        return;
}
