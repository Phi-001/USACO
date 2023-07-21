#include <iostream>
#include <vector>
#include <map>

using namespace std;

void dfs_up(int u, int p, vector<vector<int>> &adj, vector<int> &depth, vector<vector<int>> &up) {
    if (p != -1)
        depth[u] = depth[p] + 1;
    else
        depth[u] = 1;

    up[u][0] = p;
    for (int i = 0; i < 20; i++) {
        if (up[u][i] == -1) break;
        up[u][i + 1] = up[up[u][i]][i];
    }

    for (auto v : adj[u])
        if (v != p)
            dfs_up(v, u, adj, depth, up);
}

int jump(int u, int d, vector<vector<int>> &up) {
    for (int i = 0; i <= 20; i++)
        if (d & (1 << i)) u = up[u][i];

    return u;
}

int lca(int a, int b, vector<vector<int>> &up, vector<int> &depth) {
    if (depth[a] < depth[b]) swap(a, b);

    a = jump(a, depth[a] - depth[b], up);
    if (a == b) return a;

    for (int i = 20; i >= 0; i--) {
        int ta = up[a][i];
        int tb = up[b][i];
        if (ta != tb) {
            a = ta;
            b = tb;
        }
    }

    return up[a][0];
}

void dfs_table(int u, int p, vector<vector<int>> &adj, vector<map<int, int>> &table, vector<vector<int>> &up, vector<int> &depth, vector<int> &type) {
    for (int i = 0; i <= 20; i++) {
        if (depth[u] & (1 << i)) break;
        for (auto [ k, v ] : table[up[u][i]]) {
            table[u][k] += v;
        }
    }

    table[u][type[u]]++;

    for (auto v : adj[u])
        if (v != p)
            dfs_table(v, u, adj, table, up, depth, type);
}

int count(int u, int t, vector<vector<int>> &up, vector<int> &depth, vector<map<int, int>> &table) {
    int ans = 0;
    int d = depth[u];

    for (int i = 0; i <= 20; i++) {
        if (d & (1 << i)) {
            if (table[u].count(t)) ans += table[u][t];
            u = up[u][i];
        }
    }

    return ans;
}

int main() {
    if (fopen("milkvisits.in", "r")) {
        freopen("milkvisits.in", "r", stdin);
        freopen("milkvisits.out", "w", stdout);
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> type(n);

    for (int i = 0; i < n; i++)
        cin >> type[i];

    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> depth(n);
    vector<vector<int>> up(n, vector<int>(21, -1));

    dfs_up(0, -1, adj, depth, up);

    vector<map<int, int>> table(n);

    dfs_table(0, -1, adj, table, up, depth, type);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        a--; b--;

        int l = lca(a, b, up, depth);

        int ca = count(a, c, up, depth, table);
        int cb = count(b, c, up, depth, table);
        int clca = count(l, c, up, depth, table);
        int p = type[l] == c;

        if ((ca + cb - 2 * clca + p) == 0) cout << "0";
        else cout << "1";
    }

    cout << "\n";

    return 0;
}
