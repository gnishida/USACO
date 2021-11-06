#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>


using namespace std;

struct TreeNode {
	int id;
	int next_index;
	unordered_map<int, TreeNode*> children;

	TreeNode(int id, int next_index) {
		this->id = id;
		this->next_index = next_index;
	}
};

void duplicate(TreeNode* node, vector<int>& ans) {
	if (node->id >= 0) {
		ans[node->id]--;
		node->id = -1;
	}
}

void expand(TreeNode* node, const vector<string>& strs) {
	if (node->id >= 0 && node->next_index >= 0 && node->next_index < strs[node->id].length()) {
		const string& str = strs[node->id];
		const char& letter = str[node->next_index];
		node->children[letter - 'a'] = new TreeNode(node->id, node->next_index + 1);
		node->next_index = -1;
	}
}

void traverse(TreeNode* node, const vector<string>& strs, int id, int index, vector<int>& ans) {
	if (index >= strs[id].length()) return;

	const string& str = strs[id];

	TreeNode* child;
	if (node->children.find(str[index] - 'a') != node->children.end()) {
		child = node->children[str[index] - 'a'];
		
		expand(child, strs);

		if (child->id != id) {
			duplicate(child, ans);
		}

		traverse(child, strs, id, index + 1, ans);
	} else {
		ans[id] += str.length() - index;
		child = new TreeNode(id, index + 1);
		node->children[str[index] - 'a'] = child;
	}
}

int main() {
	ifstream in("standingout.in");
	int N;
	in >> N;

	TreeNode* root = new TreeNode(-1, 0);

	vector<string> strs(N);
	vector<int> ans(N, 0);
	for (int i = 0; i < N; i++) {
		in >> strs[i];

		for (int j = 0; j < strs[i].length(); j++) {
			traverse(root, strs, i, j, ans);
		}
	}

	ofstream out("standingout.out");
	for (int i = 0; i < N; i++) {
		out << ans[i] << endl;
	}

	return  0;
}