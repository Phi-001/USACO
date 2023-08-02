#include <cstdio>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<int> r(n);
    for (int i = 0; i < n; i++) cin >> r[i];

    long long ans = 1e18;
    for (int i = 0; i < n; i++) {
        // dp[i][j] = use i + 1 doors with last at j
        // minimum cost between 0 and j
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, 1e18));

        dp[0][0] = 0;

        for (int j = 1; j <= k; j++) {
            for (int l = 0; l < n; l++) {
                long long psum = 0;
                for (int m = 1; m + l <= n; m++) {
                    psum += (m - 1) * r[(l + m + i) % n];
                    dp[j][m + l] = min(dp[j][m + l], dp[j - 1][l] + psum);
                }
            }
        }

        ans = min(ans, dp[k][n]);
    }

    cout << ans;

    return 0;
}
