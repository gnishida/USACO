#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> findPrimes(int N) {
	vector<int> primes;
	vector<bool> isPrime(N + 1, true);

	primes.push_back(1);
	for (int x = 2; x <= N; x++) {
		if (!isPrime[x]) continue;

		primes.push_back(x);
		for (int y = x * 2; y <= N; y += x) {
			isPrime[y] = false;
		}
	}

	return primes;
}

int main() {
	ifstream in("exercise.in");
	int N, M;
	in >> N >> M;

	vector<int> primes = findPrimes(N);
	int P = primes.size();

	// Initialization
	vector<vector<long long>> DP(N + 1, vector<long long>(P + 1, 0));
	for (int i = 0; i <= N; i++) {
		DP[i][0] = 1;
	}
	for (int i = 0; i <= P; i++) {
		DP[0][i] = 1;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j < P; j++) {
			DP[i][j] = DP[i][j - 1];
			long long x = primes[j];
			while (i - x >= 0) {
				DP[i][j] = (DP[i][j] + DP[i - x][j - 1] * x) % M;
				x = (x * primes[j]) % M;
			}
		}
	}

	ofstream out("exercise.out");
	out << DP[N][P - 1] << endl;

	return 0;
}

