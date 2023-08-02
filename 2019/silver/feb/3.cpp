#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <set>
#include <functional>

using namespace std;

bool dfs(vector<vector<pair<int, bool>>> &adj, vector<int> &col, int current) {
    for (auto [ v, d ] : adj[current]) {
        int c = d ? 1 - col[current] : col[current];
        if (col[v] == -1) {
            col[v] = c;
            if (!dfs(adj, col, v)) return false;
        } else if (col[v] != c) {
            return false;
        }
    }

    return true;
}

int main() {
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, bool>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        char t;
        cin >> t >> a >> b;
        a--; b--;
        bool d = t == 'D';

        adj[a].push_back({ b, d });
        adj[b].push_back({ a, d });
    }

    int zeros = 0;
    vector<int> col(n, -1);
    for (int i = 0; i < n; i++) {
        if (col[i] == -1) {
            zeros += 1;
            col[i] = 0;
            if (!dfs(adj, col, i)) {
                cout << 0;
                return 0;
            }
        }
    }

    cout << 1;
    for (int i = 0; i < zeros; i++) {
        cout << 0;
    }

    return 0;
}
