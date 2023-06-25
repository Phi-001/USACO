#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

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

    int size(int a) {
        return -p[find(a)];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (p[a] > p[b]) swap(a, b);

        p[a] += p[b];
        p[b] = a;
    }
};

int main() {
    if (fopen("mootube.in", "r")) {
        freopen("mootube.in", "r", stdin);
        freopen("mootube.out", "w", stdout);
    }

    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> edge(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int p, q, r;
        cin >> p >> q >> r;
        p--; q--;
        edge[i] = { r, p, q };
    }

    sort(edge.begin(), edge.end());
    reverse(edge.begin(), edge.end());

    vector<array<int, 3>> query(q);
    for (int i = 0; i < q; i++) {
        int v, k;
        cin >> k >> v;
        v--;
        query[i] = { k, v, i };
    }

    sort(query.begin(), query.end());
    reverse(query.begin(), query.end());

    DSU dsu(n);

    int e = 0;
    int a = 0;

    vector<int> ans(q);

    while (a < q) {
        while (e < n - 1 && edge[e][0] >= query[a][0]) {
            dsu.unite(edge[e][1], edge[e][2]);
            e++;
        }
        ans[query[a][2]] = dsu.size(query[a][1]) - 1;
        a++;
    }

    for (auto a : ans) {
        cout << a << "\n";
    }

    return 0;
}
