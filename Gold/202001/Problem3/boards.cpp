#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
  
int main() {
    ifstream in("boards.in");
    int N, P;
    in >> N >> P;
   
    vector<pair<pair<int, int>, pair<int, int>>> springs(P);
	vector<pair<pair<int, int>, pair<int, int>>> events(P * 2);
	for (int i = 0; i < P; ++i) {
        int x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;

        springs[i] = {{x1, y1}, {x2, y2}};
        events[i * 2] = {{x1, y1}, {i, 1}};
        events[i * 2 + 1] = {{x2, y2}, {i, -1}};
	}

	sort(events.begin(), events.end());

    vector<int> DP(P, N * 2);
    map<int,int> m;
	m[0] = N * 2;

    int ans = N * 2;
	for (auto& e : events) {
        const auto& index = e.second.first;
        const auto& type = e.second.second;
        const auto& x1 = springs[index].first.first;
        const auto& y1 = springs[index].first.second;
        const auto& x2 = springs[index].second.first;
        const auto& y2 = springs[index].second.second;

		if (type == 1) {
            auto it = m.upper_bound(y1);
            it = prev(it);
			DP[index] = x1 + y1 + it->second - x2 - y2;
            ans = min(ans, DP[index]);
		} else {
            auto it = m.upper_bound(y2);
            it = prev(it);
            int new_d = DP[index];
            if (it->second > new_d) {
                it++;
            	while (it != m.end() && it->second > new_d) {
                    m.erase(it++);
                }
            	m[y2] = new_d;
            }
		}
	}

    ofstream out("boards.out");
	out << ans << endl;

    return 0;
}
