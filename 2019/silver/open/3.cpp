#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <set>

using namespace std;

struct Rect {
    int minx;
    int miny;
    int maxx;
    int maxy;
};

Rect unite(Rect a, Rect b) {
    return {
        min(a.minx, b.minx),
        min(a.miny, b.miny),
        max(a.maxx, b.maxx),
        max(a.maxy, b.maxy),
    };
}

Rect dfs(vector<vector<int>> &adj, vector<bool> &visited, int current, vector<pair<int, int>> &cows) {
    visited[current] = true;

    Rect rect = { cows[current].first, cows[current].second, cows[current].first, cows[current].second };
    for (auto v : adj[current]) {
        if (visited[v]) continue;
        rect = unite(dfs(adj, visited, v, cows), rect);
    }

    return rect;
}

int main() {
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cows[i] = { x, y };
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visited(n);

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        Rect rect = dfs(adj, visited, i, cows);
        ans = min(ans, 2 * (rect.maxx - rect.minx + rect.maxy - rect.miny));
    }

    cout << ans;

    return 0;
}
