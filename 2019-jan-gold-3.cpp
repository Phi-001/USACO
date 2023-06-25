#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int dfs(int u, vector<vector<int>> &child, vector<int> &subtree, vector<int> &c) {
    subtree[u] += c[u];

    for (auto v : child[u])
        subtree[u] += dfs(v, child, subtree, c);

    return subtree[u];
}

int main() {
    if (fopen("shortcut.in", "r")) {
        freopen("shortcut.in", "r", stdin);
        freopen("shortcut.out", "w", stdout);
    }

    int n, m, t;
    cin >> n >> m >> t;

    vector<int> c(n);
    for (int i = 0; i < n; i++)
        cin >> c[i];

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--; b--;

        adj[a].push_back({ b, t });
        adj[b].push_back({ a, t });
    }

    vector<pair<long long, int>> shortest(n, { 1e18, 1e9 });

    priority_queue<pair<pair<long long, int>, int>> q;
    q.push({ { 0, 1 }, 0 });

    while (!q.empty()) {
        auto [ path, u ] = q.top();
        q.pop();

        auto [ d, prev ] = path;
        d = -d;
        prev = -prev;

        if (shortest[u] <= make_pair(d, prev)) continue;
        shortest[u] = { d, prev };


        for (auto [ v, w ] : adj[u])
            q.push({ { -(d + w), -u }, v });
    }

    vector<vector<int>> child(n);
    for (int i = 1; i < n; i++) {
        child[shortest[i].second].push_back(i);
    }

    vector<int> subtree(n);

    dfs(0, child, subtree, c);

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        long long save = (shortest[i].first - t) * subtree[i];
        ans = max(ans, save);
    }

    cout << ans;

    return 0;
}
