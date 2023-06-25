#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    // dp[i][j] = min temper for i + 1 breakout from first j + 1
    vector<vector<int>> dp(n, vector<int>(n, 1e9));

    int temper = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] != i) temper++;
        dp[0][i] = temper;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = i; k <= j; k++) {
                int temper = 0;
                for (int l = k; l <= j; l++) {
                    if (c[l] != l - k) temper++;
                }

                dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + temper);
            }
        }
    }

    for (int i = 0; i < n; i++) cout << dp[i][n - 1] << "\n";

    return 0;
}
