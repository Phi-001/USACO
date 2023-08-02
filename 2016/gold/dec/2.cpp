#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <stack>
#include <set>
#include <functional>

using namespace std;

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, a, b;
    cin >> t >> a >> b;

    vector<bool> dp(t + 1);
    dp[0] = true;

    for (int i = 1; i <= t; i++) {
        if (i - a >= 0) dp[i] = dp[i] || dp[i - a];
        if (i - b >= 0) dp[i] = dp[i] || dp[i - b];
    }

    for (int i = 0; i <= t; i++) {
        dp[i / 2] = dp[i / 2] || dp[i];
    }

    for (int i = 1; i <= t; i++) {
        if (i - a >= 0) dp[i] = dp[i] || dp[i - a];
        if (i - b >= 0) dp[i] = dp[i] || dp[i - b];
    }

    for (int i = t; i >= 0; i--) {
        if (dp[i]) {
            cout << i;
            break;
        }
    }

    return 0;
}
