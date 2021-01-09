#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream in("taming.in");
	int N;
	in >> N;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		in >> A[i];
	}

	vector<vector<vector<int>>> DP(N, vector<vector<int>>(N + 1, vector<int>(N + 1, N + 1)));
	vector<vector<int>> minVal(N, vector<int>(N + 1, N + 1));
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			DP[i][1][i] = (A[i] == i ? 0 : 1);
		} else {
			DP[i][1][i] = DP[i - 1][1][i - 1] + (A[i] == i ? 0 : 1);
		}
		minVal[i][1] = DP[i][1][i];
	}

	for (int i = 1; i < N; i++) {
		for (int j = 2; j <= N; j++) {
			// for k = 0
			if (minVal[i - 1][j - 1] <= N) {
				DP[i][j][0] = minVal[i - 1][j - 1] + (A[i] == 0 ? 0 : 1);
			}
			minVal[i][j] = DP[i][j][0];

			for (int k = 1; k <= N; k++) {
				if (DP[i - 1][j][k - 1] <= N) {
					DP[i][j][k] = DP[i - 1][j][k - 1] + (A[i] == k ? 0 : 1);
					minVal[i][j] = min(minVal[i][j], DP[i][j][k]);
				}
			}
		}
	}

	ofstream out("taming.out");
	for (int i = 0; i < N; i++) {
		out << minVal[N - 1][i + 1] << endl;
	}


	return 0;
}