#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int mod = 1e9 + 7;

long long binexp(long long a, int b) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> w(n);
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        int s, c;
        cin >> s >> c;
        w[i] = s;
        r[i] = c - 1;
    }

    vector<long long> comb(n);
    vector<long long> dp(k + 1);

    dp[0] = 1;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < w.size(); j++) {
            if (i - w[j] >= 0) {
                dp[i] = (dp[i] + dp[i - w[j]]) % mod;
                if (i == k) comb[r[j]] = (comb[r[j]] + dp[i - w[j]]) % mod;
            }
        }
    }

    vector<int> exp(26);

    for (int i = 0; i < m; i++) {
        char g;
        cin >> g;

        exp[g - 'A']++;
    }

    long long ans = 1;

    for (int i = 0; i < 26; i++) {
        if (exp[i] == 0) continue;

        long long sum = 0;
        for (int j = 0; j < n; j++) sum = (sum + binexp(comb[j], exp[i])) % mod;
        ans = (ans * sum) % mod;
    }

    cout << ans;

    return 0;
}
