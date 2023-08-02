#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

struct SegTree {
    int n;
    vector<int> t;

    SegTree (int size) {
        n = size;
        t.resize(2 * n);
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
    if (fopen("sleepy.in", "r")) {
        freopen("sleepy.in", "r", stdin);
        freopen("sleepy.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        p[i] = x;
    }

    SegTree tree(n);

    tree.update(p[n - 1], 1);

    int k = n - 1;
    while (p[k] > p[k - 1]) {
        tree.update(p[k - 1], 1);
        k--;
    }

    vector<int> ans;

    for (int i = 0; i < k; i++) {
        ans.push_back(tree.query(0, p[i]) + k - i - 1);
        tree.update(p[i], 1);
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }

    return 0;
}
