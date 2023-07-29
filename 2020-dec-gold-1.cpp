#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int main() {
    int n, d;
    cin >> n >> d;

    vector<string> farm(n);

    for (int i = 0; i < n; i++)
        cin >> farm[i];

    vector<vector<int>> dist(n, vector<int>(n, -1));

    {
        queue<pair<int, pair<int, int>>> q;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (farm[i][j] == '#') q.push({ 0, { i, j } });

        while (!q.empty()) {
            auto [ d, c ] = q.front();
            auto [ x, y ] = c;
            q.pop();
            if (dist[x][y] != -1) continue;
            dist[x][y] = d;

            for (int i = 0; i < 4; i++) {
                if (0 <= x + dx[i] && x + dx[i] < n && 0 <= y + dy[i] && y + dy[i] < n)
                    q.push({ d + 1, { x + dx[i], y + dy[i] } });
            }
        }
    }

    vector<vector<int>> time(n, vector<int>(n, 1e9));
    vector<vector<bool>> reach(n, vector<bool>(n));
    queue<pair<int, pair<int, int>>> q;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (farm[i][j] == 'S') q.push({ 0, { i, j } });

    auto around = [&](int x, int y, int size) {
        for (int i = 0; i <= size; i++) {
            reach[x + i][y + (size - i)] = true;
            reach[x - i][y + (size - i)] = true;
            reach[x + i][y - (size - i)] = true;
            reach[x - i][y - (size - i)] = true;
        }
    };

    while (!q.empty()) {
        auto [ t, c ] = q.front();
        auto [ x, y ] = c;
        q.pop();
        int size = t / 2 / d;

        if (time[x][y] <= t) continue;
        if (dist[x][y] <= size) continue;

        if (t % 2 == 1) {
            around(x, y, size);
            q.push({ t + 1, { x, y } });
        } else {
            time[x][y] = t;
            around(x, y, size);
            for (int i = 0; i < 4; i++) {
                if (0 <= x + dx[i] && x + dx[i] < n && 0 <= y + dy[i] && y + dy[i] < n)
                    q.push({ t + 1, { x + dx[i], y + dy[i] } });
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (reach[i][j]) ans++;

    cout << ans;

    return 0;
}
