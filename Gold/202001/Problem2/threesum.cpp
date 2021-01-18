#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream in("threesum.in");
    int N, Q;
    in >> N >> Q;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        in >> A[i];
    }

    vector<vector<int>> queries(N, vector<int>(N, -1));
    for (int i = 0; i < Q; i++) {
        int a, b;
        in >> a >> b;
        if (a > b) swap(a, b);
        queries[a - 1][b - 1] = i;
    }

    vector<int> ans(Q);
    for (int i = 0; i < N; i++) {
        unordered_map<int, int> S;
        int cnt = 0;
        for (int j = i + 1; j < N; j++) {
            int negsum = -A[i] - A[j];
            if (S.find(negsum) != S.end()) {
                cnt += S[negsum];
            }

            if (queries[i][j] >= 0) {
                ans[queries[i][j]] = cnt;
            }

            S[A[j]]++;
        }
    }

    ofstream out("threesum.out");
    for (int i = 0; i < Q; i++) {
        out << ans[i] << endl;
    }

    return 0;
}