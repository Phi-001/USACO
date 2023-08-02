#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <cstdio>

using namespace std;

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<int> skill(n);
    for (int i = 0; i < n; i++) cin >> skill[i];

    // max sum with a team ending at i - 1
    vector<int> dp(n + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_skill = -1;
        int max_sum = -1;
        for (int j = i - 1; j >= max(0, i - k); j--) {
            max_skill = max(max_skill, skill[j]);
            max_sum = max(max_sum, dp[j] + max_skill * (i - j));
        }
        dp[i] = max_sum;
    }

    cout << dp[n];

    return 0;
}
