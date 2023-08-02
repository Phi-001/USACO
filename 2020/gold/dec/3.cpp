#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

int main() {
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    string s;
    cin >> s;

    vector<vector<int>> cost(m, vector<int>(m));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            cin >> cost[i][j];

    for (int k = 0; k < m; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    // dp1[i][c] = min cost at pos i with first c
    // dp2[i][c] = min cost at pos i with last c
    vector<vector<int>> dp1(n, vector<int>(m, 1e9));
    vector<vector<int>> dp2(n, vector<int>(m, 1e9));

    // psum[i][c] = psum of cost to change chars up to i to c
    vector<vector<int>> psum(n, vector<int>(m));

    for (int c = 0; c < m; c++) {
        int ch = cost[s[0] - 'a'][c];
        dp1[0][c] = ch;
        psum[0][c] = ch;
        if (k == 1) dp2[0][c] = ch;
    }

    for (int i = 1; i < n; i++) {
        for (int c = 0; c < m; c++)
            psum[i][c] = psum[i - 1][c] + cost[s[i] - 'a'][c];

        int l = 1e9;
        for (int c = 0; c < m; c++)
            l = min(l, dp2[i - 1][c]);

        for (int c = 0; c < m; c++)
            dp1[i][c] = l + cost[s[i] - 'a'][c];

        for (int c = 0; c < m; c++) {
            dp2[i][c] = dp2[i - 1][c] + cost[s[i] - 'a'][c];

            if (i >= k - 1) dp2[i][c] = min(dp2[i][c], dp1[i - k + 1][c] + psum[i][c] - psum[i - k + 1][c]);
        }
    }

    int ans = 1e9;
    for (int c = 0; c < m; c++)
        ans = min(ans, dp2[n - 1][c]);

    cout << ans;

    return 0;
}
