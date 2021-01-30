#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;

    std::unordered_map<char, int> indices;
    for (int i = 0; i < str.size(); i++) {
        if (indices.find(str[i]) == indices.end()) {
            indices[str[i]] = indices.size();
        }
    }

    int N = indices.size();

    vector<vector<int>> adj(N, vector<int>(N));
    for (int i = 1; i < str.size(); i++) {
        adj[indices[str[i - 1]]][indices[str[i]]]++;
    }

    vector<int> DP(1 << N);
    DP[0] = 1;
    for (int i = 1; i < (1 << N); i++) {
        DP[i] = str.size();
        for (int j = 0; j < N; j++) {
            // j-th letter is included in current sequence S
            if ((i & (1 << j)) != 0) {
                // get the best score for sequence (S \ j-th letter)
                int sum = DP[i ^ (1 << j)];

                for (int k = 0; k < N; k++) {
                    // If k-th letter is included in the set,
                    if ((i & (1 << k)) != 0) {
                        sum += adj[j][k];
                    }
                }
                DP[i] = min(DP[i], sum);
            }
        }
    }

    cout << DP[(1 << N) - 1] << endl;

    return 0;
}