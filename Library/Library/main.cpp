#include "usaco.h"

#include <assert.h>

using namespace std;

void testBIT() {
	// array [0, 0, 0, 0, 0]
	BIT bit(5);

	// update to [1, 0, 0, 0, 0]
	bit.add(0, 1);

	// update to [1, 0, 1, 0, 0]
	bit.add(2, 1);

	// update to [1, 0, 1, 1, 0]
	bit.add(3, 1);

	// get sum from 0 to 0-th element
	assert(bit.query(0) == 1);

	// get sum from 0 to 2nd element
	assert(bit.query(2) == 2);

	// get sum from 0 to 4th element
	assert(bit.query(4) == 3);

	// update to [0, 0, 1, 1, 0]
	bit.add(0, -1);

	// get sum from 0 to 0-th element
	assert(bit.query(0) == 0);

	// get sum from 0 to 2nd element
	assert(bit.query(2) == 1);

	// get sum from 0 to 4th element
	assert(bit.query(4) == 2);
}

void testSegmentTree() {
	// array [0, 0, 0, 0, 0]
	SegmentTree segTree(5);

	// update to [1, 0, 0, 0, 0]
	segTree.add(0, 1);

	// update to [1, 0, 1, 0, 0]
	segTree.add(2, 1);

	// update to [1, 0, 1, 1, 0]
	segTree.add(3, 1);

	// get sum from 0 to 0-th element
	assert(segTree.query(0, 0) == 1);

	// get sum from 0 to 2nd element
	assert(segTree.query(0, 2) == 2);

	// get sum from 0 to 4th element
	assert(segTree.query(0, 4) == 3);

	// get sum from 2nd to 4th element
	assert(segTree.query(2, 4) == 2);

	// update to [0, 0, 1, 1, 0]
	segTree.add(0, -1);

	// get sum from 0 to 0-th element
	assert(segTree.query(0, 0) == 0);

	// get sum from 0 to 2nd element
	assert(segTree.query(0, 2) == 1);

	// get sum from 0 to 4th element
	assert(segTree.query(0, 4) == 2);

	// get sum from 2nd to 4th element
	assert(segTree.query(2, 4) == 2);
}

int main() {
	testBIT();
	testSegmentTree();

	return 0;
}
