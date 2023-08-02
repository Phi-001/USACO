#include <cstdio>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

struct SegTree {
    int n;
    vector<int> t;

    SegTree (vector<int> a) {
        n = a.size();
        t.resize(2 * n);

        for (int i = n ; i < 2 * n; i++) t[i] = a[i - n];
        for (int i = n - 1; i > 0; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }

    void update(int i, int k) {
        for (t[i += n] += k; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }
};

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);

    int n;
    cin >> n;

    SegTree tree1(vector<int>(n + 1));
    vector<long long> ans(n);

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        int inv = tree1.query(a + 1, n + 1);
        tree1.update(a, 1);

        if (a + 1 <= n - 1) ans[a + 1] += inv;
    }

    long long psum = 0;
    for (int i = 0; i < n; i++) {
        psum += ans[i];
        cout << psum << "\n";
    }

    return 0;
}
