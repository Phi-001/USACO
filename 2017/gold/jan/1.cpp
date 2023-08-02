#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

struct SegTree {
    int n;
    vector<int> t;

    SegTree (int size) {
        n = size;
        t.resize(2 * n);
    }

    void update(int i, int k) {
        for (t[i += n] += k; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

int main() {
    if (fopen("bphoto.in", "r")) {
        freopen("bphoto.in", "r", stdin);
        freopen("bphoto.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> h(n);
    vector<pair<int, int>> compress(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        h[i] = a;
        compress[i] = { a, i };
    }

    sort(compress.begin(), compress.end());

    vector<int> index(n);

    for (int i = 0; i < n; i++) {
        index[compress[i].second] = i;
    }

    vector<int> l(n);
    SegTree ltree(n);

    for (int i = 0; i < n; i++) {
        l[i] = ltree.query(index[i] + 1, n);
        ltree.update(index[i], 1);
    }

    vector<int> r(n);
    SegTree rtree(n);

    for (int i = n - 1; i >= 0; i--) {
        r[i] = rtree.query(index[i] + 1, n);
        rtree.update(index[i], 1);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (max(l[i], r[i]) > 2 * min(l[i], r[i])) ans++;
    }

    cout << ans;

    return 0;
}
