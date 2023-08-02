#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <array>

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

using namespace std;

int main() {
    if (fopen("visitfj.in", "r")) {
        freopen("visitfj.in", "r", stdin);
        freopen("visitfj.out", "w", stdout);
    }

    int n, t;
    cin >> n >> t;

    vector<vector<int>> cost(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    vector<vector<vector<long long>>> ans(n, vector<vector<long long>>(n, vector<long long>(3, 1e18)));

    priority_queue<pair<long long, array<int, 3>>> q;
    q.push({ 0, { 0, 0, 0 }});

    while (!q.empty()) {
        auto [ d, state ] = q.top();
        auto [ x, y, s ] = state;
        q.pop();

        d = -d;

        if (ans[x][y][s % 3] <= d) continue;
        ans[x][y][s % 3] = d;

        s++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= ny && ny < n && 0 <= nx && nx < n) {
                q.push({ -(d + t + (s % 3 == 0 ? cost[nx][ny] : 0)), { nx, ny, s } });
            }
        }
    }

    long long out = 1e18;

    for (int i = 0; i < 3; i++) {
        out = min(out, ans[n - 1][n - 1][i]);
    }

    cout << out;

    return 0;
}
