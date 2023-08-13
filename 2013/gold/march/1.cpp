#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    if (fopen("cowrun.in", "r")) {
        freopen("cowrun.in", "r", stdin);
        freopen("cowrun.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    p[n] = 0;

    sort(p.begin(), p.end());

    int idx;
    for (int i = 0; i < p.size(); i++)
        if (p[i] == 0) idx = i;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 1e9)));

    dp[idx][idx][0] = 0;
    dp[idx][idx][1] = 0;

    for (int l = 1; l <= n; l++) {
        for (int a = 0; a + l <= n; a++) {
            int b = a + l;
            dp[a][b][0] = min(dp[a][b][0], dp[a + 1][b][0] + abs(p[a] - p[a + 1]) * (n - l + 1));
            dp[a][b][0] = min(dp[a][b][0], dp[a + 1][b][1] + abs(p[a] - p[b]) * (n - l + 1));
            dp[a][b][1] = min(dp[a][b][1], dp[a][b - 1][0] + abs(p[b] - p[a]) * (n - l + 1));
            dp[a][b][1] = min(dp[a][b][1], dp[a][b - 1][1] + abs(p[b] - p[b - 1]) * (n - l + 1));
        }
    }

    cout << min(dp[0][n][0], dp[0][n][1]) << "\n";

    return 0;
}
