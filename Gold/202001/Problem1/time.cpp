#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("time.in");
    int N, M, C;
    in >> N >> M >> C;

    vector<int> moneys(N);
    for (int i = 0; i < N; i++) {
        in >> moneys[i];
    }

    vector<vector<int>> edges(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        in >> a >> b;
        edges[a - 1].push_back(b - 1);
    }

    vector<vector<int>> DP(1000, vector<int>(N, -1));
    DP[0][0] = 0;
    int ans = 0;
    for (int t = 1; t < 1000; t++) {
        for (int u = 0; u < N; u++) {
            if (DP[t - 1][u] == -1) continue;

            for (const auto& v : edges[u]) {
                int new_d = DP[t - 1][u] + moneys[v];
                if (new_d > DP[t][v]) {
                    DP[t][v] = new_d;
                }
            }
        }

        if (DP[t][0] >= 0) {
            ans = max(ans, DP[t][0] - C * t * t);
        }
    }

    ofstream out("time.out");
    out << ans << endl;

    return 0;
}
