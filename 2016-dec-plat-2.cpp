#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 9;

int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> john(n);
    for (int i = 0; i < n; i++) cin >> john[i];

    vector<int> paul(m);
    for (int i = 0; i < m; i++) cin >> paul[i];

    sort(john.begin(), john.end());
    sort(paul.begin(), paul.end());

    // dp[i][j][k] = largest score cow is at i, j with k member
    vector<vector<vector<long long>>> dp(k, vector<vector<long long>>(n, vector<long long>(m)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[0][i][j] = paul[j] < john[i];
        }
    }

    for (int t = 1; t < k; t++) {
        vector<vector<long long>> psum(n, vector<long long>(m));

        for (int i = 0; i < n; i++) {
            psum[i][0] = dp[t - 1][i][0];
            for (int j = 1; j < m; j++)
                psum[i][j] = (psum[i][j - 1] + dp[t - 1][i][j]) % mod;
        }

        for (int j = 0; j < m; j++)
            for (int i = 1; i < n; i++)
                psum[i][j] = (psum[i][j] + psum[i - 1][j]) % mod;

        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (paul[j] < john[i])
                    dp[t][i][j] = psum[i - 1][j - 1];
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = (ans + dp[k - 1][i][j]) % mod;

    cout << ans;

    return 0;
}
