#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream in("teamwork.in");
	int N, K;
	in >> N >> K;
	
	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		in >> A[i];
	}

	vector<int> DP(N + 1, 0);
	DP[0] = 0;
	for (int i = 1; i <= N; i++) {
		int val = 0;
		for (int k = 0; k < min(K, i); k++) {
			val = max(val, A[i - 1 - k]);
			DP[i] = max(DP[i], DP[i - 1 - k] + val * (k + 1));
		}
	}

	ofstream out("teamwork.out");
	out << DP[N] << endl;

	return 0;
}