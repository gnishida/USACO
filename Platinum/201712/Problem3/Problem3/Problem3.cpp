#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

// Check if the first K elements make a loop
bool check(int N, int K, const vector<int>& jumps) {
	vector<int> nums(N, 0);
	for (int i = 0; i < K; i++) {
		nums[jumps[i]]++;
	}

	int total = 0;
	for (int i = 0; i < N; i++) {
		total += nums[i];
		if (total > i) {
			return true;
		}
	}
	return false;
}

int main() {
	int N;
	ifstream in("greedy.in");
	in >> N;
	vector<int> jumps(N);
	for (int i = 0; i < N; i++) {
		int cut;
		in >> cut;
		jumps[i] = N - cut - 1;
	}

	// Binary search
	int l = 0;
	int r = N - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(N, mid + 1, jumps)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}

	ofstream out("greedy.out");
	out << N - 1 - l;

	return 0;
}