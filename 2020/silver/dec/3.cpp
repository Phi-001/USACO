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

void dfs(int v, int p, vector<vector<int>> &adj, vector<int> &component, int id, string &type) {
    component[v] = id;

    for (auto c : adj[v]) {
        if (c == p) continue;
        if (type[v] == type[c]) dfs(c, v, adj, component, id, type);
    }
}

int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string type;
    cin >> type;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> component(n);
    int id = 1;
    for (int i = 0; i < n; i++) {
        if (component[i]) continue;
        dfs(i, -1, adj, component, id, type);
        id++;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;

        a--; b--;

        if (component[a] == component[b]) {
            cout << (int) (type[a] == c);
        } else {
            cout << 1;
        }
    }

    return 0;
}
