#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    vector<int> t;
    int n;

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
    int n;
    cin >> n;

    vector<int> last(n, -1);
    SegTree tree(n);

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        b--;

        ans += tree.query(last[b] + 1, i);

        if (last[b] != -1) tree.update(last[b], 0);
        tree.update(i, 1);
        last[b] = i;
    }

    cout << ans;

    return 0;
}
