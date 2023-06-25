#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

void dfs1(int u, int p, vector<vector<int>> &adj, vector<int> &bessie) {
    if (p != -1) bessie[u] = bessie[p] + 1;
    else bessie[u] = 0;

    for (auto v : adj[u])
        if (v != p) dfs1(v, u, adj, bessie);
}

void dfs2(int u, int p, vector<vector<int>> &adj, vector<int> &farmer) {
    for (auto v : adj[u])
        if (v != p) dfs2(v, u, adj, farmer);

    farmer[u] = 1e9;

    for (auto v : adj[u])
        if (v != p) farmer[u] = min(farmer[u], farmer[v] + 1);

    if (farmer[u] == 1e9)
        farmer[u] = 0;
}

int dfs(int u, int p, vector<vector<int>> &adj, vector<int> &bessie, vector<int> &farmer) {
    int ans = 0;

    for (auto v : adj[u]) {
        if (v != p) {
            if (bessie[v] - farmer[v] == 1 || bessie[v] == farmer[v]) ans++;
            else ans += dfs(v, u, adj, bessie, farmer);
        }
    }

    return ans;
}

int main() {
    if (fopen("atlarge.in", "r")) {
        freopen("atlarge.in", "r", stdin);
        freopen("atlarge.out", "w", stdout);
    }

    int n, k;
    cin >> n >> k;
    k--;

    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> bessie(n);
    vector<int> farmer(n);

    dfs1(k, -1, adj, bessie);
    dfs2(k, -1, adj, farmer);

    cout << dfs(k, -1, adj, bessie, farmer);

    return 0;
}
