#pragma once

#include <vector>

using namespace std;

// Binary indexed tree for numbers [0, ..., N - 1].
class BIT {
public:
	BIT(int N) {
		this->N = N;
		data.resize(N + 1, 0);
	}

	// Add val to the index-th element
	void add(int index, int val) {
		index++;
		while (index <= N) {
			data[index] += val;
			index += index & -index;
		}
	}

	// Get sum from 0 to index-th element
	int sum(int index) {
		index++;
		int sum = 0;
		while (index > 0) {
			sum += data[index];
			index -= index & -index;
		}
		return sum;
	}

private:
	int N;
	vector<int> data;
};
