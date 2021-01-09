#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class BIT {
public:
	BIT(int N) {
		this->N = N;
		data.resize(N + 1, 0);
	}

	void update(int index, int val) {
		index++;
		while (index <= N) {
			data[index] += val;
			index += index & -index;
		}
	}

	int query(int index) {
		index++;
		int sum = 0;
		while (index > 0) {
			sum += data[index];
			index -= index & -index;
		}
		return sum;
	}

private:
	int N;
	vector<int> data;
};


int main(void) {
	ifstream in("sort.in");
	int N;
	in >> N;

	vector<pair<int, int>> A(N);
	for (int i = 0; i < N; i++) {
		int x;
		in >> x;
		A[i] = { x, i };
	}
	sort(A.begin(), A.end());

	BIT bit(N);
	int answer = 1;
	vector<int> BIT(N + 1, 0);
	for (int i = 0; i < N - 1; i++) {
		bit.update(A[i].second, 1);
		answer = max(answer, i + 1 - bit.query(i));
	}

	ofstream out("sort.out");
	out << answer << "\n";

	return 0;
}
