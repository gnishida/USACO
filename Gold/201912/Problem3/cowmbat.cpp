#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Floyd-Warshall for shotest path from all nodes
// edgse contain edge <v, weight>
vector<vector<int>> floyd_warshall(int N, vector<vector<int>>& edges) {
	vector<vector<int>> DP(N, vector<int>(N, -1));

	// Initialize the distance between nodes
    DP = edges;

	for (int k = 0; k < N; k++) {
		for (int u = 0; u < N; u++) {
			for (int v = 0; v < N; v++) {
				DP[u][v] = min(DP[u][v], DP[u][k] + DP[k][v]);
			}
		}
	}

	return DP;
}

int main() {
    ifstream in("cowmbat.in");
    int N, M, K;
    in >> N >> M >> K;

    string S;
    in >> S;

    vector<vector<int>> A(M, vector<int>(M));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            in >> A[i][j];
        }
    }

    A = floyd_warshall(M, A);

    // Initialize DP table
    vector<vector<int>> DP(N + 1, vector<int>(M, numeric_limits<int>::max()));
    vector<int> minDP(N + 1, numeric_limits<int>::max());
    minDP[0] = 0;

    // DP
    vector<int> sumDiffs(M, 0);
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < M; j++) {
            int x = S[i - 1] - 'a';

            if (DP[i - 1][j] < numeric_limits<int>::max()) {
                DP[i][j] = DP[i - 1][j] + A[x][j];
            }

            sumDiffs[j] += A[x][j];
            if (i - K >= 0) {
                if (minDP[i - K] < numeric_limits<int>::max()) {
                    DP[i][j] = min(DP[i][j], minDP[i - K] + sumDiffs[j]);
                }

                int y = S[i - K] - 'a';
                sumDiffs[j] -= A[y][j];
            }

            minDP[i] = min(minDP[i], DP[i][j]);
        }
    }

    ofstream out("cowmbat.out");
    out << minDP[N] << endl;


    return 0;
}