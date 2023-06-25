#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int mod = 1e9 + 7;

int ways(int c, vector<int> &h, int h_max, int n) {
    vector<vector<long long>> dp(n, vector<long long>(h_max + 1));

    for (int i = 0; i <= h[0]; i++) dp[0][i] = 1;

    for (int i = 1; i < n; i++) {
        vector<long long> psum(h[i] + 1);

        psum[c] = dp[i - 1][c];
        for (int k = c + 1; k <= h[i]; k++) psum[k] = (psum[k - 1] + dp[i - 1][k]) % mod;
        for (int k = c; k <= h[i]; k++) dp[i][k] = psum[h[i] - k + c];
    }

    return dp[n - 1][c];
}

int main() {
    int n;
    cin >> n;

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    int h_max = -1;
    int h_min = 1e9;
    for (int i = 0; i < n; i++) {
        h_max = max(h_max, h[i]);
        h_min = min(h_min, h[i]);
    }

    if (n % 2 == 0) {
        cout << ways(0, h, h_max, n);
    } else {
        long long ans = 0;
        for (int i = 0; i <= h_min; i++) ans = (ans + ways(i, h, h_max, n)) % mod;
        cout << ans;
    }
}
