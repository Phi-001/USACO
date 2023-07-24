#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct SegTree {
    vector<int> t;
    int n;

    SegTree (vector<int> a) {
        n = a.size();
        t.resize(2 * n);

        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void update(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
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
    if (fopen("sort.in", "r")) {
        freopen("sort.in", "r", stdin);
        freopen("sort.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = { x, i };
    }

    sort(a.begin(), a.end());

    vector<int> idx(n);

    for (int i = 0; i < n; i++)
        idx[a[i].second] = i;

    SegTree tree((vector<int>(n)));

    int ans = 1;

    for (int i = 0; i < n; i++) {
        ans = max(ans, tree.query(i, n));
        tree.update(idx[i], 1);
    }

    cout << ans;

    return 0;
}
