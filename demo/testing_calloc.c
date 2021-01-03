// Descrpition: This is to test calloc on WSL as it appears to be misbehaving.
//

#include <stdlib.h>

int main() {
	char *mem = calloc(20, 1);
	free(mem);

	return 0;
}
