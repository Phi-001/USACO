#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <set>

using namespace std;

int dfs(vector<vector<int>> &adj, vector<bool> &visited, int current) {
    visited[current] = true;

    int size_component = 1;
    for (auto v : adj[current]) {
        if (visited[v]) continue;
        size_component += dfs(adj, visited, v);
    }

    return size_component;
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> cows(n);
    vector<int> power(n);
    for (int i = 0; i < n; i++) {
        int x, y, p;
        cin >> x >> y >> p;
        cows[i] = { x, y };
        power[i] = p;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        int p = power[i];
        for (int j = 0; j < n; j++) {
            int dx = cows[i].first - cows[j].first;
            int dy = cows[i].second - cows[j].second;
            int d2 = dx * dx + dy * dy;
            if (d2 < p * p) {
                adj[i].push_back(j);
            }
        }
    }

    int ans = -1;
    for (int i = 0; i < n; i++) {
        vector<bool> visited(n);
        ans = max(ans, dfs(adj, visited, i));
    }

    cout << ans;

    return 0;
}
