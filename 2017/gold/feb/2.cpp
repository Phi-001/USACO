#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    if (fopen("nocross.in", "r")) {
        freopen("nocross.in", "r", stdin);
        freopen("nocross.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<vector<int>> c(2, vector<int>(n));
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < n; i++)
            cin >> c[j][i];

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(4, -1e9)));

    dp[0][0][0b11] = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k < 4; k++) {
                if (i < n) {
                    dp[i + 1][j][k & ~0b10] = max(dp[i + 1][j][k & ~0b10], dp[i][j][k]);
                    if (!(k & 0b01) && (j > 0) && abs(c[0][i] - c[1][j - 1]) <= 4)
                        dp[i + 1][j][0b11] = max(dp[i + 1][j][0b11], dp[i][j][k] + 1);
                }

                if (j < n) {
                    dp[i][j + 1][k & ~0b01] = max(dp[i][j + 1][k & ~0b01], dp[i][j][k]);
                    if (!(k & 0b10) && (i > 0) && abs(c[0][i - 1] - c[1][j]) <= 4)
                        dp[i][j + 1][0b11] = max(dp[i][j + 1][0b11], dp[i][j][k] + 1);
                }

                if (i < n && j < n) {
                    dp[i + 1][j + 1][0b00] = max(dp[i + 1][j + 1][0b00], dp[i][j][k]);
                    if (abs(c[0][i] - c[1][j]) <= 4)
                        dp[i + 1][j + 1][0b11] = max(dp[i + 1][j + 1][0b11], dp[i][j][k] + 1);
                }
            }
        }
    }

    int ans = -1e9;

    for (int i = 0; i < 4; i++) {
        ans = max(ans, dp[n][n][i]);
    }

    cout << ans;

    return 0;
}
