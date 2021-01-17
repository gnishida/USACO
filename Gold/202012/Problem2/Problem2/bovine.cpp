#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	const long long MOD = 1000000007;
	const string BASES = "AGCT";

	ios_base::sync_with_stdio(false); cin.tie(0);

	string s;
	cin >> s;

	vector<vector<vector<vector<long long>>>> dp(s.size(), vector<vector<vector<long long>>>(4, vector<vector<long long>>(4, vector<long long>(4, 0))));

	for (int n = 0; n < 4; n++) {
		for (int l = 0; l < 4; l++) {
			if (s[0] == '?' || s[0] == BASES[l]) {
				dp[0][n][l][l] = 1;
			}
		}
	}

	for (int k = 1; k < s.size(); k++) {
		for (int m2 = 0; m2 < 4; m2++) {
			if (s[k] == '?' || s[k] == BASES[m2]) {
				for (int n = 0; n < 4; n++) {
					for (int l = 0; l < 4; l++) {
						for (int m = 0; m < 4; m++) {
							if (m != m2) {
								dp[k][n][l][m2] = (dp[k][n][l][m2] + dp[k - 1][n][l][m]) % MOD;
							}
							if (n == m) {
								dp[k][l][m2][m2] = (dp[k][l][m2][m2] + dp[k - 1][n][l][m]) % MOD;
							}
						}
					}
				}
			}
		}
	}

	long long answer = 0;
	for (int l = 0; l < 4; l++) {
		for (int m = 0; m < 4; m++) {
			answer = (answer + dp[s.size() - 1][m][l][m]) % MOD;
		}
	}

	cout << answer << endl;

	return 0;
}