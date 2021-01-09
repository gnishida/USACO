#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
	int left;
	int right;
};

int main() {
	ifstream in("snowboots.in");
	int N, B;
	in >> N >> B;

	map<int, vector<int>> feets; // <feet, vector of index>
	for (int i = 0; i < N; i++) {
		int f;
		in >> f;
		feets[f].push_back(i);
	}

	vector<pair<int, pair<int, int>>> boots(B); // <depth, <step, index>>
	for (int i = 0; i < B; i++) {
		int d, s;
		in >> d >> s;
		boots[i] = { d, {s, i} };
	}

	// sort boots
	sort(boots.rbegin(), boots.rend());

	// initialize linked list
	vector<Node> nodes(N);
	for (int i = 0; i < N; i++) {
		nodes[i].left = i - 1;
		nodes[i].right = i + 1;
	}

	vector<int> ans(B, 1);
	int boot_index = 0;
	int maxGap = 1;
	for (auto it = feets.rbegin(); it != feets.rend(); it++) {
		const auto feet = it->first;
		if (feet == 0) break;

		while (boots[boot_index].first >= feet) {
			const auto& step = boots[boot_index].second.first;
			const auto& ans_index = boots[boot_index].second.second;

			if (step < maxGap) ans[ans_index] = 0;

			boot_index++;
		}
		
		// Remove the cells of the current feet
		for (const auto& index : it->second) {
			const auto& left_index = nodes[index].left;
			const auto& right_index = nodes[index].right;

			// Update max gap and linked list
			maxGap = max(maxGap, right_index - left_index);
			nodes[left_index].right = right_index;
			nodes[right_index].left = left_index;
		}
	}

	while (boot_index < boots.size()) {
		const auto& step = boots[boot_index].second.first;
		const auto& ans_index = boots[boot_index].second.second;

		if (step < maxGap) ans[ans_index] = 0;

		boot_index++;
	}

	ofstream out("snowboots.out");
	for (const auto& a : ans) {
		out << a << endl;
	}

	return 0;
}