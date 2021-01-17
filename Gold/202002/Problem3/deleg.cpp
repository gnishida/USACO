#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class TreeNode {
public:
    int parent;
    int size;
};

int dfs(const vector<vector<int>>& edges, int u, int parent, vector<TreeNode>& nodes) {
    nodes[u].parent = parent;
    nodes[u].size = 1;

    for (const auto& v : edges[u]) {
        if (v == parent) continue;

        nodes[u].size += dfs(edges, v, u, nodes);
    }

    return nodes[u].size;
}

int solve(int N, const vector<vector<int>>& edges, const vector<TreeNode>& nodes, int K) {
    vector<int> remainders(K, 0);

    for (int u = 0; u < N; u++) {
        int num = 0;

        int totalSize = 0;
        for (const auto& v : edges[u]) {
            if (v == nodes[u].parent) continue;

            int rem = nodes[v].size % K;
            if (rem > 0) {
                if (remainders[K - rem] > 0) {
                    remainders[K - rem]--;
                    num--;
                } else {
                    remainders[rem]++;
                    num++;
                }
            }
            totalSize += nodes[v].size;
        }

        int rem = (N - 1 - totalSize) % K;
        if (rem > 0) {
            if (remainders[K - rem] > 0) {
                if (--remainders[K - rem] == 0) {
                    num--;
                }
            } else {
                remainders[rem]++;
                num++;
            }
        }

        if (num != 0) return 0;
    }

    return 1;    
}

int main() {
    ifstream in("deleg.in");
    int N;
    in >> N;

    vector<vector<int>> edges(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        in >> a >> b;
        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }

    vector<TreeNode> nodes(N);
    dfs(edges, 0, -1, nodes);

    ofstream out("deleg.out");
    for (int k = 1; k < N; k++) {
        if ((N - 1) % k != 0) {
            out << 0;
            continue;
        }

        out << solve(N, edges, nodes, k);
    }
    out << endl;

    return 0;
}