#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void dfs(int v, vector<vector<int>> &adj, vector<bool> &active, vector<int> &ans, int i) {
    if (active[v]) return;
    active[v] = true;
    ans[v] = i;

    for (auto u : adj[v])
        dfs(u, adj, active, ans, i);
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<pair<char, int>> queries(q);
    vector<pair<int, int>> edges;
    vector<bool> ea;
    vector<bool> active(n, true);

    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;

        queries[i].first = t;

        if (t == 'A') {
            int x, y;
            cin >> x >> y;
            x--; y--;
            edges.push_back({ x, y });
            ea.push_back(true);
            queries[i].second = edges.size() - 1;
        } else if (t == 'D') {
            int x;
            cin >> x;
            x--;
            active[x] = false;
            queries[i].second = x;
        } else {
            int e;
            cin >> e;
            e--;
            ea[e] = false;
            queries[i].second = e;
        }
    }

    vector<vector<int>> adj(n);

    for (int i = 0; i < edges.size(); i++) {
        if (ea[i]) {
            auto [ x, y ] = edges[i];
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    vector<int> ans(n, -1);

    for (int i = 0; i < n; i++) {
        if (active[i]) {
            active[i] = false;
            dfs(i, adj, active, ans, q);
        }
    }

    for (int i = q - 1; i >= 0; i--) {
        auto [ t, x ] = queries[i];
        if (t == 'D') {
            dfs(x, adj, active, ans, i);
        } else if (t == 'R') {
            auto [ a, b ] = edges[x];
            adj[a].push_back(b);
            adj[b].push_back(a);
            if (active[b]) dfs(a, adj, active, ans, i);
            if (active[a]) dfs(b, adj, active, ans, i);
        }
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << "\n";

    return 0;
}
