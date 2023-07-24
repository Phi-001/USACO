#include <iostream>
#include <vector>

using namespace std;

int main() {
    if (fopen("snakes.in", "r")) {
        freopen("snakes.in", "r", stdin);
        freopen("snakes.out", "w", stdout);
    }

    int n, k;
    cin >> n >> k;

    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    vector<vector<int>> m(n, vector<int>(n));

    for (int l = 0; l < n; l++) {
        int x = 0;
        for (int r = l; r < n; r++) {
            x = max(x, s[r]);
            m[l][r] = x;
        }
    }

    // dp[i][k][j] = at i'th position used k changes with last change at j
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(n, 1e9)));

    dp[0][0][0] = 0;

    for (int i = 1; i < n; i++) {
        for (int l = 0; l <= k; l++) {
            for (int j = 1; j <= i; j++) {
                dp[i][l][j] = dp[i - 1][l][j - 1] + j * (m[i - j][i] - m[i - j][i - 1]) + (m[i - j][i] - s[i]);
                if (l != 0) dp[i][l][0] = min(dp[i][l][0], dp[i - 1][l - 1][j - 1]);
            }
        }
    }

    int ans = 1e9;

    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[n - 1][k][i]);
    }

    cout << ans;

    return 0;
}
