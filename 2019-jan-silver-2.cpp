#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <stack>
#include <set>
#include <functional>

using namespace std;

pair<int, int> floodfil(vector<vector<bool>> &board, vector<vector<bool>> &visited, int x, int y, int n) {
    stack<pair<int, int>> frontier;
    frontier.push({ x, y });

    int area = 0;
    int perimeter = 0;

    while (!frontier.empty()) {
        auto [ r, c ] = frontier.top();
        frontier.pop();

        if (r < 0 || r >= n || c < 0 || c >= n) {
            perimeter++;
            continue;
        }

        if (!board[r][c]) {
            visited[r][c] = true;
            perimeter++;
            continue;
        }

        if (visited[r][c]) continue;

        visited[r][c] = true;
        area++;

        frontier.push({ r - 1, c });
        frontier.push({ r + 1, c });
        frontier.push({ r, c - 1 });
        frontier.push({ r, c + 1 });
    }

    return { area, perimeter };
}

int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<vector<bool>> ice(n, vector<bool>(n));

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            ice[i][j] = row[j] == '#';
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(n));

    int ma = -1;
    int mp = 1e9;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                auto [ area, perimeter ] = floodfil(ice, visited, i, j, n);

                if (area >= ma) {
                    if (area == ma) mp = min(mp, perimeter);
                    else {
                        ma = area;
                        mp = perimeter;
                    }
                }
            }
        }
    }

    cout << ma << " " << mp;

    return 0;
}
