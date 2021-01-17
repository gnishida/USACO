#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007;

long long mypow(long long num, long long e) {
    if (e == 1) return num;

    long long h = e / 2;
    long long ret = mypow(num, h);
    ret = (ret * ret) % MOD;
    if (e % 2 == 1) {
        ret = (ret * num) % MOD;
    }
    return ret;
}

int main() {
    ifstream in("help.in");
    int N;
    in >> N;

    vector<pair<int, pair<int, int>>> events(N * 2);
    for (int i = 0; i < N; i++) {
        int l, r;
        in >> l >> r;
        events[i * 2] = {l, {i, 1}};
        events[i * 2 + 1] = {r, {i, -1}};
    }

    sort(events.begin(), events.end());

    vector<vector<long long>> DP(N * 2 + 1, vector<long long>(4, 0));
    int k = 0;
    for (int i = 1; i <= N * 2; i++) {
        const auto& type = events[i - 1].second.second;
        if (type == 1) {
            k++;
            DP[i][0] = (DP[i - 1][0] * 2 + DP[i - 1][2]) % MOD;
            DP[i][1] = (DP[i - 1][1] * 2 + 1) % MOD;
            DP[i][2] = DP[i - 1][2];
            DP[i][3] = (mypow(2, k) - 1 - DP[i - 1][2] + MOD) % MOD;
        } else {
            k--;
            DP[i][0] = (DP[i - 1][0] + 1) % MOD;
            DP[i][1] = (DP[i - 1][1] + MOD - 1) % MOD;
            DP[i][2] = (DP[i - 1][2] * 2 + 1) % MOD;
            DP[i][3] = (DP[i - 1][2] + DP[i - 1][3] - DP[i][2] + MOD) % MOD;
        }
    }

    ofstream out("help.out");
    out << (DP[N * 2][0] + DP[N * 2][1]) % MOD << endl;

    return 0;
}