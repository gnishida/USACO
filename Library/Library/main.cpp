#include "usaco.h"

#include <assert.h>


using namespace std;


void testBinarySearch() {
	vector<int> A = { 1, 3, 4, 8, 8, 8, 10 };
	BinarySearch bs(A);
	assert(bs.lowerBound(2) == 1); // 1 [3] 4  8  8  8  10
	assert(bs.lowerBound(3) == 1); // 1 [3] 4  8  8  8  10
	assert(bs.lowerBound(7) == 3); // 1  3  4 [8] 8  8  10
	assert(bs.lowerBound(8) == 3); // 1  3  4 [8] 8  8  10
	assert(bs.lowerBound(9) == 6); // 1  3  4  8  8  8 [10]
}

void testMergeSort() {
	vector<int> A = { 3, 8, 4, 1, 5, 7, 2, 6 };
	auto result = mergeSort(A, 0, A.size() - 1);
	assert(result.size() == A.size());
	assert(result[0] == 1);
	assert(result[1] == 2);
	assert(result[2] == 3);
	assert(result[3] == 4);
	assert(result[4] == 5);
	assert(result[5] == 6);
	assert(result[6] == 7);
	assert(result[7] == 8);
}

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

void testPrim() {
	vector<vector<int>> edges = {
		{0, 4, 13, 7, 7},
		{4, 0, 9, 3, 7},
		{13, 9, 0, 10, 14},
		{7, 3, 10, 0, 4},
		{7, 7, 14, 4, 0}
	};
	assert(prim(5, edges), 20);
}

int main() {
	testBinarySearch();
	testMergeSort();
	testBIT();
	testSegmentTree();

	testPrim();

	return 0;
}
