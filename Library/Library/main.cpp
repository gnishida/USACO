#include "BIT.h"

#include <assert.h>

using namespace std;

int main() {
	// array [0, 0, 0, 0, 0]
	BIT bit(5);

	// update to [1, 0, 0, 0, 0]
	bit.add(0, 1);

	// update to [1, 0, 1, 0, 0]
	bit.add(2, 1);

	// get sum from 0 to 0-th element
	assert(bit.sum(0) == 1);

	// get sum from 0 to 2nd element
	assert(bit.sum(2) == 2);

	// get sum from 0 to 4th element
	assert(bit.sum(4) == 2);

	// update to [0, 0, 1, 0, 0]
	bit.add(0, -1);

	// get sum from 0 to 0-th element
	assert(bit.sum(0) == 0);

	// get sum from 0 to 2nd element
	assert(bit.sum(2) == 1);

	return 0;
}
