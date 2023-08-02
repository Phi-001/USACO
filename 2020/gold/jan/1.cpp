#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <cstdio>

using namespace std;

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    int n, m, c;
    cin >> n >> m >> c;

    vector<int> mooney(n);
    for (int i = 0; i < n; i++) cin >> mooney[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<vector<int>> dp(n, vector<int>(1001, -1e9));
    dp[0][0] = 0;

    for (int t = 1; t <= 1000; t++) {
        for (int i = 0; i < n; i++) {
            for (auto v : adj[i]) {
                dp[v][t] = max(dp[v][t], dp[i][t - 1] + mooney[v]);
            }
        }
    }

    int ans = -1;
    for (int t = 0; t <= 1000; t++) {
        ans = max(ans, dp[0][t] - c * t * t);
    }

    cout << ans << "\n";

    return 0;
}
