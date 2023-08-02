#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <cstdio>

using namespace std;

const int MAX = 200000;
static int root[MAX];

int find(int node) {
    return root[node] < 0 ? node : root[node] = find(root[node]);
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return a;

    if (root[b] < root[a]) swap(a, b);

    root[a] += root[b];
    root[b] = a;

    return a;
}

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> q(n);

    for (int i = 0; i < n; i++) {
        int query;
        cin >> query;
        q[i] = query - 1;
    }

    unordered_set<int> components;
    vector<bool> added(n);
    vector<bool> ans(n);

    for (int i = 0; i < MAX; i++) root[i] = -1;

    for (int i = n - 1; i >= 0; i--) {
        added[q[i]] = true;

        for (auto v : adj[q[i]]) {
            if (added[v]) {
                components.erase(find(q[i]));
                components.erase(find(v));
                components.insert(unite(v, q[i]));
            }
        }

        if (components.count(find(q[i])) == 0) components.insert(q[i]);

        ans[i] = components.size() == 1;
    }

    for (int i = 0; i < n; i++) {
        if (ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
