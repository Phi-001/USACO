#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    if (fopen("checklist.in", "r")) {
        freopen("checklist.in", "r", stdin);
        freopen("checklist.out", "w", stdout);
    }

    int h, g;
    cin >> h >> g;

    vector<pair<int, int>> holstein(h);

    for (int i = 0; i < h; i++) {
        int x, y;
        cin >> x >> y;
        holstein[i] = { x, y };
    }

    vector<pair<int, int>> guernsey(g);

    for (int i = 0; i < g; i++) {
        int x, y;
        cin >> x >> y;
        guernsey[i] = { x, y };
    }

    vector<vector<vector<long long>>> dp(h + 1, vector<vector<long long>>(g + 1, vector<long long>(2, 1e18)));
    dp[1][0][0] = 0;

    auto dist = [&](pair<int, int> a, pair<int, int> b) {
        long long dx = a.first - b.first;
        long long dy = a.second - b.second;
        return dx * dx + dy * dy;
    };

    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= g; j++) {
            if (i >= 2) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + dist(holstein[i - 2], holstein[i - 1]));
            if (j >= 1 && i >= 1) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1] + dist(holstein[i - 1], guernsey[j - 1]));
            if (j >= 2) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + dist(guernsey[j - 2], guernsey[j - 1]));
            if (j >= 1 && i >= 1) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + dist(holstein[i - 1], guernsey[j - 1]));
        }
    }

    cout << dp[h][g][0];

    return 0;
}
