#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <set>
#include <functional>

using namespace std;

void dfs(vector<vector<int>> &adj, vector<bool> &visited, int current, vector<int> &component) {
    visited[current] = true;
    component.push_back(current);

    for (auto v : adj[current]) {
        if (visited[v]) continue;
        dfs(adj, visited, v, component);
    }
}

void dfs2(vector<vector<pair<int, int>>> &adj, vector<bool> &visited, int current, vector<int> &component, int size) {
    visited[current] = true;
    component.push_back(current);

    for (auto [ v, w ] : adj[current]) {
        if (w < size) continue;
        if (visited[v]) continue;
        dfs2(adj, visited, v, component, size);
    }
}

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

int main() {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_perm(n);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        if (p == i) continue;
        adj_perm[i].push_back(p);
        adj_perm[p].push_back(i);
    }

    vector<vector<int>> components;
    vector<bool> visited(n);

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        vector<int> component;
        dfs(adj_perm, visited, i, component);
        components.push_back(component);
    }

    if (components.size() == n) {
        cout << -1;
        return 0;
    }

    int max_size = -1;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({ b, w });
        adj[b].push_back({ a, w });
        max_size = max(max_size, w);
    }

    int ans = first_possible(0, max_size, [&](int size) {
        vector<int> cs(n);
        int nc = 0;
        vector<bool> visited(n);
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            vector<int> component;
            dfs2(adj, visited, i, component, size);
            for (auto v : component) {
                cs[v] = nc;
            }
            nc++;
        }

        for (int i = 0; i < components.size(); i++) {
            int k = cs[components[i][0]];
            for (int j = 1; j < components[i].size(); j++) {
                if (cs[components[i][j]] != k) return true;
            }
        }

        return false;
    }) - 1;

    cout << ans;

    return 0;
}
