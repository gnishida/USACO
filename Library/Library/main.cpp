#include "usaco.h"
#include "treap.h"

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
	assert(prim(5, edges) == 20);
}

void testBiconnectedComponents() {
	
	vector<vector<int>> edges = {
		{2, 3},
		{2, 4},
		{0, 1, 3},
		{0, 2},
		{1, 5, 7},
		{4, 6},
		{5, 7, 8},
		{4, 6, 8},
		{6, 7}
	};
	/*
	vector<vector<int>> edges = {
		{1, 4},
		{0, 2, 3},
		{1, 3},
		{1, 2},
		{0, 5, 7},
		{4, 6},
		{5, 7, 8},
		{4, 6, 8},
		{6, 7}
	};
	*/
	vector<int> groups = biconnectedComponents(9, edges, 0);

	vector<int> expected = { 2, 1, 2, 2, 0, 0, 0, 0, 0 };
	for (int i = 0; i < groups.size(); i++) {
		assert(groups[i] == expected[i]);
	}
}

void testTreap() {
	struct TreapNode* root = nullptr;
	root = TreapInsert(root, 50);
	root = TreapInsert(root, 30);
	root = TreapInsert(root, 20);
	root = TreapInsert(root, 40);
	root = TreapInsert(root, 70);
	root = TreapInsert(root, 60);
	root = TreapInsert(root, 80);

	root = TreapDeleteNode(root, 20);

	TreapNode* result = TreapSearch(root, 50);
	assert(result);
	assert(result->key == 50);

	assert(TreapSearch(root, 20) == nullptr);
}

int main() {
	testBinarySearch();
	testMergeSort();
	testBIT();
	testSegmentTree();

	testPrim();

	testBiconnectedComponents();

	testTreap();

	return 0;
}
