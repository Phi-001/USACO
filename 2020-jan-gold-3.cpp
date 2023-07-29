#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct SegTree {
    vector<int> t;
    int n;

    SegTree (vector<int> a) {
        n = a.size();
        t.resize(2 * n);
        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, int v) {
        for (t[i] = max(t[i += n], v); i > 1; i >>= 1) t[i >> 1] = max(t[i], t[i ^ 1]);
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

int main() {
    if (fopen("boards.in", "r")) {
        freopen("boards.in", "r", stdin);
        freopen("boards.out", "w", stdout);
    }

    int n, p;
    cin >> n >> p;

    vector<pair<pair<int, int>, int>> s(2 * p);
    vector<int> ys;
    for (int i = 0; i < 2 * p; i++) {
        int x, y;
        cin >> x >> y;
        s[i] = { { x, y }, i };
        ys.push_back(y);
    }

    vector<int> cost(p);
    for (int i = 0; i < p; i++) {
        auto [ x1, y1 ] = s[i * 2].first;
        auto [ x2, y2 ] = s[i * 2 + 1].first;
        cost[i] = (x2 - x1) + (y2 - y1);
    }

    sort(ys.begin(), ys.end());
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());

    SegTree tree((vector<int>(2 * p)));
    vector<int> m(p);

    for (auto [ c, i ] : s) {
        auto [ x, y ] = c;
        int cy = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y));
        if (i % 2 == 0) {
            tree.update(cy, m[i / 2] + cost[i / 2]);
        } else {
            m[i / 2] = tree.query(cy, 2 * p);
        }
    }

    int msave = tree.query(0, 2 * p);

    cout << 2 * n - msave;

    return 0;
}
