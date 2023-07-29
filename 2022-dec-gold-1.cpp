#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<pair<int, pair<int, int>>> cow(n);

    for (int i = 0; i < n; i++) {
        int p, c, x;
        cin >> p >> c >> x;
        cow[i] = { x, { p, c } };
    }

    sort(cow.begin(), cow.end());

    vector<vector<int>> dp(n + 1, vector<int>(a + b + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= a + b; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            auto [ x, value ] = cow[i - 1];
            auto [ p, c ] = value;
            int cost = j <= a ? min(c, a - j) + x * max(0, c - (a - j)) : x * c;
            if (j + cost <= a + b) dp[i][j] = max(dp[i][j], dp[i - 1][j + cost] + p);
        }
    }

    int ans = 0;
    for (int i = 0; i <= a + b; i++)
        ans = max(ans, dp[n][i]);

    cout << ans << "\n";

    return 0;
}
