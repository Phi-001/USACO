#include <cstdio>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

struct DSU {
    int n;
    vector<int> p;

    DSU (int size) {
        n = size;
        p.resize(n);
        fill(p.begin(), p.end(), -1);
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
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    long long a, b, n, m;
    cin >> a >> b >> n >> m;

    vector<tuple<long long, int, int>> edges;

    vector<long long> verts(n + 2);
    verts[0] = 0;
    for (int i = 0; i < n; i++) cin >> verts[i + 1];
    verts[n + 1] = a;

    vector<long long> horiz(m + 2);
    horiz[0] = 0;
    for (int i = 0; i < m; i++) cin >> horiz[i + 1];
    horiz[m + 1] = b;

    sort(verts.begin(), verts.end());
    sort(horiz.begin(), horiz.end());

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            edges.push_back({ verts[i + 1] - verts[i], (n + 1) * j + i, (n + 1) * (j + 1) + i });
        }
    }

    for (int j = 0; j <= m; j++) {
        for (int i = 0; i < n; i++) {
            edges.push_back({ horiz[j + 1] - horiz[j], (n + 1) * j + i, (n + 1) * j + i + 1 });
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu((n + 1) * (m + 1));

    long long ans = 0;

    for (auto [ w, a, b ] : edges) {
        if (w <= 0) cout << "hmmmm";
        if (dsu.unite(a, b)) ans += w;
    }

    cout << ans;

    return 0;
}
