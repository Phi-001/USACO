#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <utility>

using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int main() {
    if (fopen("radio.in", "r")) {
        freopen("radio.in", "r", stdin);
        freopen("radio.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    int fx, fy, bx, by;
    cin >> fx >> fy >> bx >> by;

    string f, b;
    cin >> f >> b;

    vector<pair<int, int>> fp(n + 1), bp(m + 1);
    fp[0] = { fx, fy };
    bp[0] = { bx, by };

    for (int i = 1; i <= n; i++) {
        int dir = -1;
        if (f[i - 1] == 'N') dir = 0;
        if (f[i - 1] == 'E') dir = 1;
        if (f[i - 1] == 'S') dir = 2;
        if (f[i - 1] == 'W') dir = 3;

        fp[i] = { fp[i - 1].first + dx[dir], fp[i - 1].second + dy[dir] };
    }

    for (int i = 1; i <= m; i++) {
        int dir = -1;
        if (b[i - 1] == 'N') dir = 0;
        if (b[i - 1] == 'E') dir = 1;
        if (b[i - 1] == 'S') dir = 2;
        if (b[i - 1] == 'W') dir = 3;

        bp[i] = { bp[i - 1].first + dx[dir], bp[i - 1].second + dy[dir] };
    }

    auto dist = [&](int i, int j) {
        int x = fp[i].first - bp[j].first;
        int y = fp[i].second - bp[j].second;
        return x * x + y * y;
    };

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));

    dp[0][0] = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i < n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + dist(i + 1, j));
            if (j < m) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + dist(i, j + 1));
            if (i < n && j < m) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + dist(i + 1, j + 1));
        }
    }

    cout << dp[n][m];

    return 0;
}
