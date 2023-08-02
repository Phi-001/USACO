#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> p;
    int n;

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
    if (fopen("fcolor.in", "r")) {
        freopen("fcolor.in", "r", stdin);
        freopen("fcolor.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<int> f(n, -1);
    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        a = dsu.find(a);
        b = dsu.find(b);

        if (f[a] == -1) f[a] = b;

        int x = f[a];
        int y = b;
        while (x >= 0 && y >= 0 && dsu.find(x) != dsu.find(y)) {
            int tx = x;
            int ty = y;
            x = dsu.find(x);
            y = dsu.find(y);
            if (f[x] < 0) f[x] = f[y];
            if (f[y] < 0) f[y] = f[x];
            x = f[x];
            y = f[y];
            dsu.unite(tx, ty);
        }
    }

    vector<int> ans(n, -1);

    int c = 1;
    for (int i = 0; i < n; i++) {
        if (ans[dsu.find(i)] == -1) ans[dsu.find(i)] = c++;
        cout << ans[dsu.find(i)] << "\n";
    }

    return 0;
}
