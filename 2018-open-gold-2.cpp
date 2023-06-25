#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

int bin_search(int lo, int hi, function<bool(int)> f) {
    while (lo < hi) {
        int mid = (hi - lo + 1) / 2 + lo;
        if (f(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    return lo;
}

bool topo_sort(vector<vector<int>> &adj, vector<int> &topo) {
    int n = adj.size();
    vector<int> in(n);

    for (int i = 0; i < n; i++) {
        for (auto v : adj[i])
            in[v]++;
    }

    priority_queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) q.push(-i);
    }

    while (!q.empty()) {
        int u = q.top();
        q.pop();

        u = -u;

        topo.push_back(u);

        for (auto v : adj[u]) {
            in[v]--;
            if (in[v] == 0)
                q.push(-v);
        }
    }

    return topo.size() == n;
}

bool acyclic(vector<vector<int>> &adj) {
    vector<int> topo;
    return topo_sort(adj, topo);
}

int main() {
    if (fopen("milkorder.in", "r")) {
        freopen("milkorder.in", "r", stdin);
        freopen("milkorder.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<vector<int>> order(m);

    for (int i = 0; i < m; i++) {
        int l;
        cin >> l;
        for (int j = 0; j < l; j++) {
            int c;
            cin >> c;
            order[i].push_back(c - 1);
        }
    }

    int work = bin_search(1, m, [&](int x) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < order[i].size() - 1; j++) {
                adj[order[i][j]].push_back(order[i][j + 1]);
            }
        }
        return acyclic(adj);
    });

    vector<int> in(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < work; i++) {
        for (int j = 0; j < order[i].size() - 1; j++) {
            adj[order[i][j]].push_back(order[i][j + 1]);
            in[order[i][j + 1]]++;
        }
    }

    vector<int> ans;
    topo_sort(adj, ans);

    for (int i = 0; i < n; i++)
        cout << ans[i] + 1 << " \n"[i == n - 1];

    return 0;
}
