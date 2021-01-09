#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct TreeNode {
	string name;
	vector<int> children;
	long long sum;  // exlude this ndoe in the path (e.g., file1)
	long long sum2; // include this node in the path (e.g., folder1/file1)
	int cnt;
};

pair<long long, int> dfs(vector<TreeNode>& treeNodes, int u) {
	if (treeNodes[u].children.size() == 0) {
		treeNodes[u].sum = treeNodes[u].name.size();
		treeNodes[u].sum2 = treeNodes[u].sum;
		treeNodes[u].cnt = 1;
		return { treeNodes[u].sum, 1 };
	} else {
		treeNodes[u].sum = 0;
		treeNodes[u].cnt = 0;
		for (const auto& v : treeNodes[u].children) {
			auto ret = dfs(treeNodes, v);
			treeNodes[u].sum += ret.first;
			treeNodes[u].cnt += ret.second;
		}

		treeNodes[u].sum2 = treeNodes[u].sum + ((int)treeNodes[u].name.size() + 1) * treeNodes[u].cnt;

		return { treeNodes[u].sum2, treeNodes[u].cnt };
	}
}

void dfs2(vector<TreeNode>& treeNodes, int u, long long sum, int cnt, vector<long long>& ans) {
	ans[u] = sum + cnt * 3 + treeNodes[u].sum;

	sum += cnt * 3 + treeNodes[u].sum;
	cnt += treeNodes[u].cnt;
	for (const auto& v : treeNodes[u].children) {
		dfs2(treeNodes, v, sum - treeNodes[v].sum2, cnt - treeNodes[v].cnt, ans);
	}
}

int main() {
	ifstream in("dirtraverse.in");
	int N;
	in >> N;

	vector<TreeNode> treeNodes(N);
	for (int i = 0; i < N; i++) {
		in >> treeNodes[i].name;

		int num_children;
		in >> num_children;
		treeNodes[i].children.resize(num_children);
		for (int j = 0; j < num_children; j++) {
			int x;
			in >> x;
			treeNodes[i].children[j] = x - 1;
		}
	}

	dfs(treeNodes, 0);

	vector<long long> ans(N);
	dfs2(treeNodes, 0, 0, 0, ans);

	long long minSum = numeric_limits<long long>::max();
	for (int i = 0; i < N; i++) {
		if (treeNodes[i].children.size() > 0) {
			minSum = min(minSum, ans[i]);
		}
	}
	ofstream out("dirtraverse.out");
	out << minSum << endl;

	return 0;
}