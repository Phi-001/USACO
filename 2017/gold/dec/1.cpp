#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

struct DSU {
    vector<int> root;
    int n;

    DSU (int size) {
        n = size;
        root.resize(n);
        fill(root.begin(), root.end(), -1);
    }

    int unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return a;

        if (root[a] > root[b]) swap(a, b);

        root[a] += root[b];
        root[b] = a;

        return a;
    }

    int find(int a) {
        return root[a] < 0 ? a : root[a] = find(root[a]);
    }

    bool connected(int a, int b) {
        a = find(a);
        b = find(b);

        return a == b;
    }
};

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> cows(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cows[i] = { x, y };
    }

    vector<pair<int, pair<int, int>>> dist;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = cows[i].first - cows[j].first;
            int dy = cows[i].second - cows[j].second;
            int d = dx * dx + dy * dy;

            dist.push_back({ d, { i, j }});
        }
    }

    sort(dist.begin(), dist.end());

    DSU dsu(n);
    int cost = 0;

    for (auto [ c, d ] : dist) {
        if (!dsu.connected(d.first, d.second)) {
            dsu.unite(d.first, d.second);
            cost = c;
        }
    }

    cout << cost;

    return 0;
}
