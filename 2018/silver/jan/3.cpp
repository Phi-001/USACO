#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <stack>
#include <set>
#include <functional>

using namespace std;

int dfs(int v, int p, vector<vector<pair<int, int>>> &adj, int k) {
    int ans = 0;

    for (auto [ c, r ] : adj[v]) {
        if (c == p) continue;
        if (r >= k) ans += 1 + dfs(c, v, adj, k);
    }

    return ans;
}

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int p, q, r;
        cin >> p >> q >> r;
        p--; q--;

        adj[p].push_back({ q, r });
        adj[q].push_back({ p, r });
    }

    for (int i = 0; i < q; i++) {
        int v, k;
        cin >> k >> v;

        cout << dfs(v - 1, -1, adj, k) << "\n";
    }

    return 0;
}
