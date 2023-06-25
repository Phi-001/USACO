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

int first_possible(int lo, int hi, function<bool(int)> f) {
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void floodfill(vector<vector<int>> &components, vector<vector<int>> &elevation, int d, int x, int y, int n, int m, int id) {
    stack<pair<int, int>> frontier;
    frontier.push({ x, y });

    while (!frontier.empty()) {
        auto [ r, c ] = frontier.top();
        frontier.pop();

        if (components[c][r]) continue;
        components[c][r] = id;

        if (r > 0 && abs(elevation[c][r - 1] - elevation[c][r]) <= d) frontier.push({ r - 1, c });
        if (c > 0 && abs(elevation[c - 1][r] - elevation[c][r]) <= d) frontier.push({ r, c - 1 });
        if (r < n - 1 && abs(elevation[c][r + 1] - elevation[c][r]) <= d) frontier.push({ r + 1, c });
        if (c < m - 1 && abs(elevation[c + 1][r] - elevation[c][r]) <= d) frontier.push({ r, c + 1 });
    }
}

int main() {
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> m >> n;

    vector<vector<int>> elevation(m, vector<int>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> elevation[i][j];
        }
    }

    vector<pair<int, int>> check_points;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int check;
            cin >> check;
            if (check) check_points.push_back({ j, i });
        }
    }

    cout << first_possible(0, 1e9, [&](int d) {
        vector<vector<int>> components(m, vector<int>(n));

        int id = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (components[i][j]) continue;
                floodfill(components, elevation, d, j, i, n, m, id);
                id++;
            }
        }

        auto c = check_points[0];
        int cid = components[c.second][c.first];

        for (int i = 1; i < check_points.size(); i++) {
            auto c = check_points[i];
            if (cid != components[c.second][c.first]) return false;
        }

        return true;
    });

    return 0;
}
