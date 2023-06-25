#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

void dfs_files(int u, int p, vector<vector<int>> &adj, vector<bool> &leaf, vector<int> &files) {
    for (auto v : adj[u])
        if (v != p)
            dfs_files(v, u, adj, leaf, files);

    for (auto v : adj[u])
        if (v != p)
            files[u] += files[v];

    if (leaf[u]) files[u] = 1;
}

void dfs_below(int u, int p, vector<vector<int>> &adj, vector<int> &size, vector<bool> &leaf, vector<int> &files, vector<long long> &below) {
    for (auto v : adj[u])
        if (v != p)
            dfs_below(v, u, adj, size, leaf, files, below);

    for (auto v : adj[u])
        if (v != p)
            below[u] += below[v] + (size[v] + 1) * files[v];

    if (leaf[u]) below[u] = -1;
}

void dfs_dist(int u, int p, vector<vector<int>> &adj, vector<long long> &dist, vector<int> &files, int total, vector<int> &size) {
    if (p != -1)
        dist[u] = dist[p] - (size[u] + 1) * files[u] + 3 * (total - files[u]);

    for (auto v : adj[u])
        if (v != p)
            dfs_dist(v, u, adj, dist, files, total, size);
}

int main() {
    if (fopen("dirtraverse.in", "r")) {
        freopen("dirtraverse.in", "r", stdin);
        freopen("dirtraverse.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<int> size(n);
    vector<bool> leaf(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        size[i] = s.size();

        int m;
        cin >> m;

        leaf[i] = (m == 0);

        vector<int> inside;

        for (int j = 0; j < m; j++) {
            int k;
            cin >> k;
            k--;

            adj[i].push_back(k);
            adj[k].push_back(i);
        }
    }

    vector<int> files(n);
    vector<long long> below(n);
    vector<long long> dist(n);
    dfs_files(0, -1, adj, leaf, files);
    dfs_below(0, -1, adj, size, leaf, files, below);
    dist[0] = below[0];
    dfs_dist(0, -1, adj, dist, files, files[0], size);

    long long ans = 1e18;
    for (int i = 0; i < n; i++) {
        if (!leaf[i]) ans = min(ans, dist[i]);
    }

    cout << ans << "\n";

    return 0;
}
