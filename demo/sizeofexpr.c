// Demonstration of sizeof <expression> syntax
//

#include <stdio.h>

int main() {
	float d = 0.4f;
	size_t d_size = sizeof d;
	printf("The size of a float is %zu\n", d_size);

	return 0;
}
