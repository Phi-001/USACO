#include <iostream>
#include <cstdio>
#include <array>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> sp(vector<vector<array<int, 3>>> &adj, int i, int start) {
    int n = adj.size();
    vector<int> dist(n, 1e9);

    priority_queue<array<int, 2>> q;
    q.push({ 0, start });

    while (!q.empty()) {
        auto [ d, u ] = q.top();
        q.pop();

        d = -d;

        if (dist[u] < d) continue;
        dist[u] = d;

        for (auto [ v, c, j ] : adj[u])
            if (j < i)
                q.push({ -(d + c), v });
    }

    return dist;
}

int main() {
    if (fopen("pump.in", "r")) {
        freopen("pump.in", "r", stdin);
        freopen("pump.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<vector<array<int, 3>>> adj(n);
    vector<array<int, 5>> edge(m);

    for (int i = 0; i < m; i++) {
        int a, b, c, f;
        cin >> a >> b >> c >> f;
        a--; b--;
        adj[a].push_back({ b, c, i });
        adj[b].push_back({ a, c, i });

        edge[i] = { f, i, a, b, c };
    }

    sort(edge.begin(), edge.end());
    reverse(edge.begin(), edge.end());

    vector<int> index(m);

    for (int i = 0; i < m; i++)
        index[edge[i][1]] = i;

    for (auto &a : adj) {
        for (auto &e : a) {
            e[2] = index[e[2]];
        }
    }

    int ans = -1;

    for (int i = 0; i < m; i++) {
        vector<int> farm = sp(adj, i, 0);
        vector<int> town = sp(adj, i, n - 1);

        int dist = min(farm[edge[i][2]] + town[edge[i][3]], farm[edge[i][3]] + town[edge[i][2]]) + edge[i][4];

        ans = max(ans, edge[i][0] * ((int) 1e6) / dist);
    }

    cout << ans;

    return 0;
}
