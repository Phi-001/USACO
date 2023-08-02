#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<bool>> pref(n, vector<bool>(n));

    for (int i = 0; i < n; i++) {
        bool b = true;
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            a--;
            pref[i][a] = b;
            if (a == i) b = false;
        }
    }

    vector<vector<long long>> dp(1 << n, vector<long long>(n));
    vector<long long> ans(1 << n);

    ans[0] = 1;
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = 1;

    for (int i = 0; i < n; i++) {
        for (int mask = 1 << i; mask < (1 << (i + 1)); mask++) {
            for (int last = 0; last <= i; last++) {
                if (!(mask & (1 << last))) continue;
                for (int j = 0; j < i; j++)
                    if (!(mask & (1 << j)) && pref[last][j])
                        dp[mask | (1 << j)][j] += dp[mask][last];
                if (pref[last][i])
                    ans[mask] += dp[mask][last];
            }

            for (int j = i; j < n; j++) {
                if (mask & (1 << j)) continue;
                dp[mask | (1 << j)][j] += ans[mask];
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;

        int h = 0;
        int g = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'H') h |= 1 << i;
            else g |= 1 << i;
        }

        cout << ans[h] * ans[g] << "\n";
    }

    return 0;
}
