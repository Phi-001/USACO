#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    if (fopen("dream.in", "r")) {
        freopen("dream.in", "r", stdin);
        freopen("dream.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    typedef array<array<int, 4>, 2> Cell;

    vector<vector<Cell>> floodfill(n, vector<Cell>(m));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 4; k++)
                for (int l = 0; l < 2; l++)
                    floodfill[j][i][l][k] = 1e9;

    vector<vector<int>> maze(n, vector<int>(m));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> maze[j][i];

    int di[4] = { 1, -1, 0, 0 };
    int dj[4] = { 0, 0, 1, -1 };

    struct State {
        int i;
        int j;
        int dir;
        int moves;
        bool smell;
    };

    queue<State> q;
    q.push({ 0, 0, 0, 0, false });

    while (!q.empty()) {
        State s = q.front();
        q.pop();

        if (floodfill[s.j][s.i][s.smell][s.dir] <= s.moves) continue;

        floodfill[s.j][s.i][s.smell][s.dir] = s.moves;

        if (maze[s.j][s.i] == 2) s.smell = true;

        if (maze[s.j][s.i] == 4) {
            s.smell = false;

            int i = s.i + di[s.dir];
            int j = s.j + dj[s.dir];
            if (j >= 0 && j < n && i >= 0 && i < m && maze[j][i] != 0 && maze[j][i] != 3) {
                q.push({ i, j, s.dir, s.moves + 1, s.smell });
                continue;
            }
        }

        for (int k = 0; k < 4; k++) {
            int i = s.i + di[k];
            int j = s.j + dj[k];
            if (j < 0 || j >= n || i < 0 || i >= m) continue;
            if (maze[j][i] == 0) continue;
            if (maze[j][i] == 3 && !s.smell) continue;
            q.push({ i, j, k, s.moves + 1, s.smell });
        }
    }

    int ans = 1e9;

    for (int k = 0; k < 4; k++) {
        ans = min(ans, floodfill[n - 1][m - 1][0][k]);
        ans = min(ans, floodfill[n - 1][m - 1][1][k]);
    }

    ans = ans == 1e9 ? -1 : ans;

    cout << (ans == 1e9 ? -1 : ans);

    return 0;
}
