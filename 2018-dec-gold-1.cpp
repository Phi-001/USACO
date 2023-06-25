#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    if (fopen("dining.in", "r")) {
        freopen("dining.in", "r", stdin);
        freopen("dining.out", "w", stdout);
    }

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--; b--;

        adj[a].push_back({ b, t });
        adj[b].push_back({ a, t });
    }

    vector<int> yumminess(n);

    for (int i = 0; i < k; i++) {
        int l, y;
        cin >> l >> y;
        l--;

        yumminess[l] = max(yumminess[l], y);
    }

    priority_queue<pair<int, pair<int, bool>>> q;

    q.push({ 0, { n - 1, false } });

    vector<vector<int>> shortest(n, vector<int>(2, 1e9));

    while (!q.empty()) {
        auto [ d, s ] = q.top();
        auto [ u, e ] = s;
        q.pop();

        d = -d;

        if (shortest[u][e] <= d) continue;

        shortest[u][e] = d;

        if (e) {
            for (auto [ v, t ] : adj[u]) {
                q.push({ -(d + t), { v, true } });
            }
        } else {
            for (auto [ v, t ] : adj[u]) {
                q.push({ -(d + t), { v, false } });
                if (yumminess[v] > 0)
                    q.push({ -(d + t - yumminess[v]), { v, true } });
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        cout << (shortest[i][0] >= shortest[i][1]) << "\n";
    }

    return 0;
}
