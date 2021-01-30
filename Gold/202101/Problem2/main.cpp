#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> breeds(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> breeds[i];
        breeds[i]--;
    }

    vector<vector<bool>> adj(K + 1, vector<bool>(K + 1));
    for (int b = 0; b < K; b++) {
        string s;
        cin >> s;
        for (int c = 0; c < K; c++) {
            adj[b][c] = (s[c] == '1');
        }
        adj[b][K] = adj[b][breeds[N - 1]];
    }
    breeds[N - 1] = K;

    vector<vector<int>> DP(K + 1, vector<int>(N, -1));
    DP[breeds[0]][0] = 0;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> Q;
    Q.push({0, {breeds[0], 0}});
    while (!Q.empty()) {
        int d = Q.top().first;
        int b = Q.top().second.first;
        int u = Q.top().second.second;
        Q.pop();

        if (d > DP[b][u]) continue;
        
        if (u >= 1) {
            int new_d = d + 1;
            if (DP[b][u - 1] == -1 || new_d < DP[b][u - 1]) {
                DP[b][u - 1] = new_d;
                Q.push({new_d, {b, u - 1}});
            }
        }
        if (u < N - 1) {
            int new_d = d + 1;
            if (DP[b][u + 1] == -1 || new_d < DP[b][u + 1]) {
                DP[b][u + 1] = new_d;
                Q.push({new_d, {b, u + 1}});
            }
        }
        if (adj[b][breeds[u]]) {
            int new_b = breeds[u];
            if (DP[new_b][u] == -1 || d < DP[new_b][u]) {
                DP[new_b][u] = d;
                Q.push({d, {new_b, u}});
            }
        }
    }

    cout << DP[K][N - 1] << endl;

    return 0;
}