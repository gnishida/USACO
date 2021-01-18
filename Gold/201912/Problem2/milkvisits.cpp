#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Query {
    Query(int index, int type, int other) : index(index), type(type), other(other) {}
    int index;
    int type;
    int other;
};

struct TreeNode {
    int depth;
    int preorder_index;
    int left;
    int right;
};

void dfs_preorder(const vector<vector<int>>& edges, int u, int parent, int depth, int& index, vector<TreeNode>& nodes) {
    nodes[u].depth = depth;
    nodes[u].left = index;
    nodes[u].preorder_index = index++;

    for (const auto& v : edges[u]) {
        if (v == parent) continue;
        dfs_preorder(edges, v, u, depth + 1, index, nodes);
    }

    nodes[u].right = index - 1;
}

int getLCA(const vector<TreeNode>& nodes, const vector<int>& ancestors, int u, int other) {
    if (nodes[other].preorder_index >= nodes[u].left && nodes[other].preorder_index <= nodes[u].right) return u;

    int depth = nodes[u].depth;
    int step = depth / 2;

    while (step > 0) {
        if (nodes[other].preorder_index < nodes[u].left || nodes[other].preorder_index > nodes[u].right) {
            depth -= step;
        } else {
            if (step == 1) break;
            depth += step;
        }
        u = ancestors[depth];
        step /= 2;
    }

    // Go up for final adjustment
    while (nodes[other].preorder_index < nodes[u].left || nodes[other].preorder_index > nodes[u].right) {
        u = ancestors[--depth];
    }

    // Go down for final adjustment
    while (true) {
        int next = ancestors[depth + 1];
        if (nodes[other].preorder_index < nodes[next].left || nodes[other].preorder_index > nodes[next].right) break;
        u = next;
        depth++;
    }

    return u;
}

void dfs(const vector<vector<int>>& edges, int u, int parent, const vector<TreeNode>& nodes, const vector<int>& T, const vector<vector<Query>>& queries, vector<int>& ancestors, vector<int>& last_found_depths, vector<bool>& ans) {
    int prev_found_depth = last_found_depths[T[u]];
    last_found_depths[T[u]] = nodes[u].depth;
    ancestors.push_back(u);

    for (const auto& query : queries[u]) {
        int lca = getLCA(nodes, ancestors, u, query.other);

        if (last_found_depths[query.type] >= nodes[lca].depth) {
            ans[query.index] = true;
        }
    }

    for (const auto& v : edges[u]) {
        if (v == parent) continue;
        dfs(edges, v, u, nodes, T, queries, ancestors, last_found_depths, ans);
    }

    last_found_depths[T[u]] = prev_found_depth;
    ancestors.pop_back();
}

int main() {
    ifstream in("milkvisits.in");
    int N, M;
    in >> N >> M;

    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        in >> T[i];
    }

    vector<vector<int>> edges(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        in >> a >> b;
        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }

    vector<vector<Query>> queries(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        in >> a >> b >> c;
        queries[a - 1].push_back({i, c, b - 1});
        queries[b - 1].push_back({i, c, a - 1});
    }

    // Assign preorder index
    vector<TreeNode> nodes(N);
    int index = 0;
    dfs_preorder(edges, 0, -1, 0, index, nodes);

    // Solve
    vector<int> ancestors;
    vector<int> last_found_depths(N + 1, -1);
    vector<bool> ans(M);
    dfs(edges, 0, -1, nodes, T, queries, ancestors, last_found_depths, ans);

    ofstream out("milkvisits.out");
    for (const auto& a : ans) {
        out << (a ? 1 : 0);
    }
    out << endl;

    return 0;
}