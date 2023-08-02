#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    if (fopen("spainting.in", "r")) {
        freopen("spainting.in", "r", stdin);
        freopen("spainting.out", "w", stdout);
    }

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> dp(n + 1);

    dp[0] = 1;
    dp[1] = m + 1;

    for (int i = 2; i < k; i++) {
        dp[i] = (dp[i - 1] + (dp[i - 1] - dp[i - 2]) * m) % mod;
    }

    for (int i = k; i <= n; i++) {
        dp[i] = (dp[i - 1] + (dp[i - 1] - dp[i - k]) * (m - 1)) % mod;
    }

    long long total = 1;
    for (int i = 0; i < n; i++)
        total = total * m % mod;

    cout << (total - (dp[n] - dp[n - 1]) + mod) % mod;

    return 0;
}
