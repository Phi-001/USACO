#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

struct DSU {
    vector<int> p;

    DSU (int size) {
        p.resize(size);
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
    int n;
    cin >> n;

    vector<vector<int>> portals(2 * n);
    vector<array<int, 3>> edges;

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;

        edges.push_back({ c, i * 4, i * 4 + 2 });
        edges.push_back({ 0, i * 4, i * 4 + 1 });
        edges.push_back({ 0, i * 4 + 2, i * 4 + 3 });

        for (int j = 0; j < 4; j++) {
            int p;
            cin >> p;
            p--;

            portals[p].push_back(4 * i + j);
        }
    }

    DSU dsu(4 * n);

    for (int i = 0; i < 2 * n; i++) {
        dsu.unite(portals[i][0], portals[i][1]);
    }

    sort(edges.begin(), edges.end());

    int ans = 0;

    for (auto e : edges) {
        if (dsu.unite(e[1], e[2])) ans += e[0];
    }

    cout << ans;

    return 0;
}
