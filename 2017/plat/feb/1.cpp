#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

struct SegTree {
    vector<long long> t;
    int n;

    SegTree (int size) : t(2 * size), n(size) {}

    void update(int i, int v) {
        for (t[i += n] += v; i > 1; i >>= 1) t[i >> 1] = t[i] + t[i ^ 1];
    }

    int query(int l, int r) {
        long long res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};

int main() {
    if (fopen("mincross.in", "r")) {
        freopen("mincross.in", "r", stdin);
        freopen("mincross.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<vector<int>> seq(2, vector<int>(n));
    vector<vector<int>> inv(2, vector<int>(n));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            x--;
            seq[i][j] = x;
            inv[i][x] = j;
        }
    }

    long long ans = 1e18;

    for (int j = 0; j < 2; j++) {
        long long cur = 0;
        SegTree tree(n);

        for (int i = 0; i < n; i++) {
            cur += tree.query(inv[1 - j][seq[j][i]], n);
            tree.update(inv[1 - j][seq[j][i]], 1);
        }

        for (int i = 0; i < n; i++) {
            cur += n - 2 * inv[1 - j][seq[j][i]] - 1;
            ans = min(ans, cur);
        }
    }

    cout << ans << "\n";

    return 0;
}
