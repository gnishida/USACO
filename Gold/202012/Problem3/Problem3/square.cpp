#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;


void solve(int N, vector<pair<int, int>>& cows, int& ans, int& eq) {
	sort(cows.begin(), cows.end());

	for (int a = 0; a < N; ++a) { // leftmost cow a
		set<int> sorted_y; // set of y-coordinates for cows a+1..b-1
		for (int b = a + 1; b < N; ++b) { // rightmost cow b
			if (a < b - 1) {
				sorted_y.insert(cows[b - 1].second);
			}

			int len = cows[b].first - cows[a].first; // side length of square
			int lo = max(cows[a].second, cows[b].second) - len;
			int hi = min(cows[a].second, cows[b].second);
			if (lo > hi) continue;

			// initialize the square as [cows[a].f,cows[b].f] x [lo,lo+len]
			vector<int> y(sorted_y.begin(), sorted_y.end());

			int l = 0;
			int r = -1;

			// find cow of lowest y-coordinate that square currently contains
			while (l < y.size() && lo >= y[l] + 1) l++;

			// find cow of highest y-coordinate that square currently contains
			while (r + 1 < y.size() && lo >= y[r + 1] - len) r++;

			// initial square currently includes cows [l,r]
			while (true) { // repeatedly increase y
				ans++;
				int yl = min(cows[a].second, cows[b].second);
				int yr = max(cows[a].second, cows[b].second);

				if (l <= r) {
					yl = min(yl, y[l]);
					yr = max(yr, y[r]);
				}
				
				eq += yr - yl == len; // width is equal to height

				// current bounding rectangle is [cows[a].f,cows[b].f] x [yl,yr]
				int leave_bottom = (l < y.size() ? y[l] + 1 : numeric_limits<int>::max());  // set will no longer include cow l
				int enter_top = (r + 1 < y.size() ? y[r + 1] - len : numeric_limits<int>::max()); // set will include cow r+1
				int change_y = min(leave_bottom, enter_top); // find min y such that set changes

				if (change_y > hi) {
					break;
				}

				l += leave_bottom == change_y;
				r += enter_top == change_y;
			}
		}
	}
}

int main() {
	int N;
	cin >> N;

	vector<pair<int, int>> cows(N);
	for (int i = 0; i < N; i++) {
		cin >> cows[i].first >> cows[i].second;
	}

	int ans = N + 1;
	int eq = 0;

	solve(N, cows, ans, eq);

	// Swap x and y
	for (auto& cow : cows) {
		swap(cow.first, cow.second);
	}

	solve(N, cows, ans, eq);

	// Subtract the eq/2 as a double count
	cout << ans - eq / 2;

	return 0;
}
