#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int t, n, k;
    cin >> t >> n >> k;

    vector<pair<int, int>> cow(n);
    for (int i = 0; i < n; i++)
        cin >> cow[i].first >> cow[i].second;

    vector<vector<pair<int, int>>> chain;
    chain.push_back({ cow[0] });
    for (int i = 1; i < n; i++) {
        if (cow[i].first - cow[i - 1].first <= k) chain.back().push_back(cow[i]);
        else chain.push_back({ cow[i] });
    }

    int ans = 0;

    for (auto &c : chain) {
        int n = c.size();
        if (t == 1) {
            if (n % 2 == 0) continue;
            int m = 1e9;
            for (int i = 0; i < n; i++)
                if (i % 2 == 0 || c[i + 1].first - c[i - 1].first <= k)
                    m = min(m, c[i].second);
            ans += m;
        } else {
            vector<pair<int, int>> dp(n + 1);
            dp[n] = { 0, -1e9 };
            for (int i = n - 1; i >= 0; i--) {
                dp[i] = dp[i + 1];
                int ub = distance(c.begin(), upper_bound(c.begin(), c.end(), make_pair(c[i].first + k, (int) 1e9)));
                if (i == 0 || i == n - 1 || c[i + 1].first - c[i - 1].first <= k || (n - i) % 2 == 0)
                    dp[i].first = max(dp[i].first, dp[ub].second + c[i].second);
                if (i == 0 || i == n - 1 || c[i + 1].first - c[i - 1].first <= k || (n - i) % 2 == 1)
                    dp[i].second = max(dp[i].second, dp[ub].first + c[i].second);
            }
            ans += n % 2 == 0 ? dp[0].first : dp[0].second;
        }
    }

    cout << ans << "\n";

    return 0;
}
