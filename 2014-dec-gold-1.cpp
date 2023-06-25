#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main() {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    int n, h;
    cin >> n >> h;

    vector<array<int, 3>> cows(n);
    for (int i = 0; i < n; i++) {
        int h, w, s;
        cin >> h >> w >> s;
        cows[i] = { h, w, s };
    }

    int ans = -1;

    vector<int> dp(1 << n, -1);

    dp[0] = 1e9;

    for (int s = 1; s < (1 << n); s++) {
        int th = 0;

        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                th += cows[i][0];
                dp[s] = max(dp[s], min(cows[i][2], dp[s ^ (1 << i)] - cows[i][1]));
            }
        }

        if (th >= h) {
            ans = max(ans, dp[s]);
        }
    }

    if (ans >= 0) cout << ans;
    else cout << "Mark is too tall";

    return 0;
}
