#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <cstdio>

using namespace std;

// whether b wins or not
int win(int a, int b) {
    if (b == 0 && a == 1) return true;
    if (b == 1 && a == 2) return true;
    if (b == 2 && a == 0) return true;
    return false;
}

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<char> joe(n);
    for (int i = 0; i < n; i++) {
        char move;
        cin >> move;
        if (move == 'H') joe[i] = 0;
        if (move == 'S') joe[i] = 1;
        if (move == 'P') joe[i] = 2;
    }

    // dp[i][j][k] = i th move, j moves changed, last played k
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(3, 0)));
    dp[0][0][0] = win(joe[0], 0);
    dp[0][0][1] = win(joe[0], 1);
    dp[0][0][2] = win(joe[0], 2);

    for (int i = 1; i < n; i++) {
        dp[i][0][0] = dp[i - 1][0][0] + win(joe[i], 0);
        dp[i][0][1] = dp[i - 1][0][1] + win(joe[i], 1);
        dp[i][0][2] = dp[i - 1][0][2] + win(joe[i], 2);
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(max(dp[i - 1][j][0], dp[i - 1][j - 1][1]), dp[i - 1][j - 1][2]) + win(joe[i], 0);
            dp[i][j][1] = max(max(dp[i - 1][j - 1][0], dp[i - 1][j][1]), dp[i - 1][j - 1][2]) + win(joe[i], 1);
            dp[i][j][2] = max(max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]), dp[i - 1][j][2]) + win(joe[i], 2);
        }
    }

    int ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = max(dp[n - 1][i][0], ans);
        ans = max(dp[n - 1][i][1], ans);
        ans = max(dp[n - 1][i][2], ans);
    }

    cout << ans << "\n";

    return 0;
}
