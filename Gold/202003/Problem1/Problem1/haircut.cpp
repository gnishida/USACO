#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> mergeSort(vector<int>& A, int left, int right, vector<long long>& inversions) {
	if (left == right) return { A[left] };

	int m = (left + right) / 2;
	auto L = mergeSort(A, left, m, inversions);
	auto R = mergeSort(A, m + 1, right, inversions);

	vector<int> ret(right - left + 1);
	int index = 0;
	int indexL = 0;
	int indexR = 0;

	while (indexL < L.size() || indexR < R.size()) {
		if (indexL < L.size() && (indexR >= R.size() || L[indexL] <= R[indexR])) {
			ret[index++] = L[indexL++];
		} else {
			inversions[R[indexR]] += L.size() - indexL;
			ret[index++] = R[indexR++];
		}
	}

	return ret;
}

int main() {
	ifstream in("haircut.in");
	int N;
	in >> N;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		in >> A[i];
	}

	vector<long long> inversions(N + 1, 0);
	mergeSort(A, 0, N - 1, inversions);

	ofstream out("haircut.out");
	long long ans = 0;
	for (int i = 0; i < N; i++) {
		out << ans << endl;
		ans += inversions[i];
	}

	return 0;
}