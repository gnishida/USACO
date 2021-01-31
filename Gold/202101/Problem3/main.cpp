#include <iostream>
#include <vector>

using namespace std;

// adds in all reachable positions from S_node where time <= bar
void add(const vector<vector<pair<int,int>>>& S, int node, int bar, vector<int>& cnt, int& uniquePos) {
    for (const auto& x : S[node]) {
        if (x.second > bar) return;
        if (cnt[x.first] == 0) {
            uniquePos++;
        }
        cnt[x.first]++;
    }
}

// removes all reachable positions from S_node where time <= bar
void remove(const vector<vector<pair<int,int>>>& S, int node, int bar, vector<int>& cnt, int& uniquePos) {
    for (const auto& x : S[node]){
        if (x.second > bar) return;
        if (cnt[x.first] == 1) {
            uniquePos--;
        }
        cnt[x.first]--;
    }
}

void dfs(const vector<int>& P, vector<int>& nodes, vector<bool>& visited, int node) {
    visited[node] = true;
    nodes.push_back(node);
    if (!visited[P[node]]) {
        dfs(P, nodes, visited, P[node]);
    }
}

int main() {
    int N, K;
    long long M;
    cin >> N >> K >> M;

    vector<pair<int, int>> A(K);
    for (int i = 0; i < K; i++) {
        cin >> A[i].first >> A[i].second;
        A[i].first--;
        A[i].second--;
    }

    vector<int> from(N);
    vector<vector<pair<int, int>>> S(N); // <pos, time>
    for (int i = 0; i < N; i++) {
        from[i] = i;
        S[i].push_back({i, 0});
    }

    // Simulate the first K swaps
    for (int i = 0; i < K; i++) {
        S[from[A[i].first]].push_back({A[i].second, i + 1});
        S[from[A[i].second]].push_back({A[i].first, i + 1});
        swap(from[A[i].first], from[A[i].second]);
    }

    // Compute array P
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        P[from[i]] = i;
    }

    vector<int> ans(N);
    vector<int> cnt(N, 0);

    // Run DFS on each cycle
    vector<int> nodes; //stores nodes currently in cycle
    vector<bool> visited(N, false);
    int uniquePos = 0;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(P, nodes, visited, i);
            long long D = M / K;
            int R = M % K;
            if (D >= nodes.size()) {
                D = nodes.size();
                R = 0;
            }

            int j = D - 1;
            for (int k = 0; k <= j; k++) {
                add(S, nodes[k], K, cnt, uniquePos);
            }

            for (int i = 0; i < nodes.size(); i++) {
                int newJ = (j + 1) % nodes.size();
                add(S, nodes[newJ], R, cnt, uniquePos);
                ans[nodes[i]] = uniquePos;
                remove(S, nodes[newJ], R, cnt, uniquePos);
                remove(S, nodes[i], K, cnt, uniquePos);
                add(S, nodes[newJ], K, cnt, uniquePos);
                j = newJ;
            }

            // reset everything from this cycle
            for (int k = 0; k < D; k++) {
            	remove(S, nodes[k], K, cnt, uniquePos);
            }
            nodes.clear();
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
