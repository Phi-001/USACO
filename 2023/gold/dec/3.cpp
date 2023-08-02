#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> p;
    int n;

    DSU (int size) {
        n = size;
        p.resize(n);
        fill(p.begin(), p.end(), -1);
    }

    int size(int a) {
        return -p[find(a)];
    }

    int find(int a) {
        return p[a] < 0 ? a : p[a] = find(p[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);

        p[a] += p[b];
        p[b] = a;

        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> degree(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }

    vector<pair<int, pair<int, int>>> edges;

    priority_queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        q.push({ -degree[i], i });

    while (!q.empty()) {
        auto [ d, v ] = q.top();
        q.pop();

        if (degree[v] == 0) continue;

        for (auto u : adj[v]) {
            if (degree[u] > 0) {
                degree[u]--;
                q.push({ -degree[u], u });
                edges.push_back({ -d, { u, v } });
            }
        }

        degree[v] = 0;
    }

    int ans = -1;

    reverse(edges.begin(), edges.end());

    DSU dsu(n);

    for (auto [ w, p ] : edges) {
        auto [ a, b ] = p;
        dsu.unite(a, b);
        ans = max(ans, w * dsu.size(a));
    }

    cout << ans;

    return 0;
}
