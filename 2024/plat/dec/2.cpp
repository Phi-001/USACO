#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const long long mod = 1e9 + 7;

struct SegTree1 {
    int n;
    vector<long long> t;

    SegTree1 (int size) : n(size), t(2 * size) {}

    void update(int i, long long v) {
        i += n;
        t[i] = (t[i] + v) % mod;
        for (; i > 1; i >>= 1) t[i >> 1] = (t[i] + t[i ^ 1]) % mod;
    }

    long long query(int l, int r) {
        long long res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = (res + t[l++]) % mod;
            if (r & 1) res = (res + t[--r]) % mod;
        }
        return res;
    }
};

struct SegTree2 {
    SegTree1 tree;

    SegTree2 (int size) : tree(size) {}

    void update(int l, int r, int v) {
        tree.update(l, v);
        if (r < tree.n) tree.update(r, mod - v);
    }

    long long query(int i) {
        return tree.query(0, i + 1);
    }
};

struct DSU1 {
    int n;
    vector<int> p;
    vector<vector<int>> inside;

    DSU1 (int size) : n(size), p(size, -1), inside(size) {
        for (int i = 0; i < n; i++)
            inside[i].push_back(i);
    }

    int find(int a) {
        return p[a] < 0 ? a : p[a] = find(p[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (p[a] > p[b]) swap(a, b);

        for (auto e : inside[b])
            inside[a].push_back(e);

        p[a] += p[b];
        p[b] = a;

        return true;
    }
};

struct DSU2 {
    int n;
    vector<int> p;
    vector<pair<int, int>> range;

    DSU2 (int size, vector<int> &idx) : n(size), p(size, -1), range(size) {
        for (int i = 0; i < n; i++)
            range[i] = { idx[i], idx[i] };
    }

    int find(int a) {
        return p[a] < 0 ? a : p[a] = find(p[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (p[a] > p[b]) swap(a, b);

        range[a] = { min(range[a].first, range[b].first),
            max(range[a].second, range[b].second) };

        p[a] += p[b];
        p[b] = a;

        return true;
    }
};

long long bin_pow(int a, int b) {
    long long sq = a;
    long long ans = 1;

    while (b > 0) {
        if (b & 1) ans = ans * sq % mod;
        sq = sq * sq % mod;
        b >>= 1;
    }

    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;

    int inv10 = bin_pow(10, mod - 2);

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges.push_back({ a, b });
    }

    vector<int> idx(n);
    {
        DSU1 dsu1(n);

        for (auto [ a, b ] : edges)
            dsu1.unite(a, b);

        for (int i = 0; i < n; i++)
            idx[dsu1.inside[dsu1.find(0)][i]] = i;
    }

    DSU2 dsu2(n, idx);
    SegTree2 tree(n);

    for (int i = 0; i < m; i++) {
        auto [ ta, tb ] = edges[i];

        int a = dsu2.find(ta);
        int b = dsu2.find(tb);

        auto [ al, ar ] = dsu2.range[a];
        auto [ bl, br ] = dsu2.range[b];

        int as = -dsu2.p[a];
        int bs = -dsu2.p[b];

        int av = tree.query(idx[ta]);
        int bv = tree.query(idx[tb]);

        if (dsu2.unite(a, b)) {
            tree.update(al, ar + 1, (i + 1) * bin_pow(10, n - as - 1) % mod);
            tree.update(bl, br + 1, (i + 1) * bin_pow(10, n - bs - 1) % mod);

            tree.update(al, ar + 1, bv * bin_pow(inv10, as) % mod);
            tree.update(bl, br + 1, av * bin_pow(inv10, bs) % mod);
        }
    }

    for (int i = 0; i < n; i++)
        cout << tree.query(idx[i]) << "\n";

    return 0;
}
