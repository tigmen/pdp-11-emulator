#include "config.h"
#include <stdio.h>
#include "memmory.h"

int main(void) {
	printf("%" PRIadr "\n", (address)(-1));

	return 0;
}
