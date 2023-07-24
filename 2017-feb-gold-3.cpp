#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    vector<int> t;
    int n;

    SegTree (vector<int> a) {
        n = a.size();
        t.resize(2 * n);

        for (int i = n; i < 2 * n; i++) t[i] = a[i - n];
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
    if (fopen("circlecross.in", "r")) {
        freopen("circlecross.in", "r", stdin);
        freopen("circlecross.out", "w", stdout);
    }

    int n;
    cin >> n;

    int ans = 0;
    vector<int> in(n, -1);
    SegTree tree((vector<int>(2 * n)));

    for (int i = 0; i < 2 * n; i++) {
        int a;
        cin >> a;
        a--;

        if (in[a] == -1) {
            in[a] = i;
            tree.update(i, 1);
        } else {
            ans += tree.query(in[a] + 1, i);
            tree.update(in[a], 0);
        }
    }

    cout << ans;

    return 0;
}
