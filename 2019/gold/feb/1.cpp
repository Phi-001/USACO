#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>

using namespace std;

struct SegTree {
    vector<int> t;
    int n;
    function<int(int, int)> f;
    int start;

    SegTree (vector<int> a, function<int(int, int)> comp, int s) {
        n = a.size();
        f = comp;
        start = s;
        t.resize(2 * n);

        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void update(int i, int k) {
        for (t[i] = f(t[i += n], k); i > 1; i >>= 1) t[i >> 1] = f(t[i], t[i ^ 1]);
    }

    int query(int l, int r) {
        int ans = start;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = f(ans, t[l++]);
            if (r & 1) ans = f(ans, t[--r]);
        }
        return ans;
    }
};

void dfs(int u, int p, vector<vector<int>> &adj, vector<int> &e, vector<int> &euler, vector<int> &start, vector<int> &end, int &i) {
    start[u] = i++;

    if (p != -1)
        euler[start[u]] = euler[start[p]] ^ e[u];
    else
        euler[start[u]] = e[u];

    for (auto v : adj[u])
        if (v != p)
            dfs(v, u, adj, e, euler, start, end, i);

    end[u] = i;
}

void dfs2(int u, int p, vector<vector<int>> &adj, vector<int> &euler2, vector<int> &index, vector<int> &inverse, int &j) {
    index[u] = euler2.size();
    int c = j++;
    inverse[c] = u;
    euler2.push_back(c);

    for (auto v : adj[u]) {
        if (v != p) {
            dfs2(v, u, adj, euler2, index, inverse, j);
            euler2.push_back(c);
        }
    }
}

int main() {
    if (fopen("cowland.in", "r")) {
        freopen("cowland.in", "r", stdin);
        freopen("cowland.out", "w", stdout);
    }

    int n, q;
    cin >> n >> q;

    vector<int> e(n);
    for (int i = 0; i < n; i++)
        cin >> e[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> euler(n);
    vector<int> start(n);
    vector<int> end(n);

    int i = 0;
    dfs(0, -1, adj, e, euler, start, end, i);

    vector<int> diff(n);
    diff[0] = euler[0];
    for (int i = 1; i < n; i++)
        diff[i] = euler[i - 1] ^ euler[i];

    SegTree tree(diff, [](int a, int b) { return a ^ b; }, 0);

    vector<int> euler2;
    vector<int> index(n);
    vector<int> inverse(n);
    int j = 0;
    dfs2(0, -1, adj, euler2, index, inverse, j);

    SegTree lca_tree(euler2, [](int a, int b) { return min(a, b); }, 1e9);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int i, v;
            cin >> i >> v;
            i--;
            tree.update(start[i], v ^ e[i]);
            if (end[i] != n) tree.update(end[i], v ^ e[i]);
            e[i] = v;
        } else {
            int i, j;
            cin >> i >> j;
            i--; j--;
            int lca = inverse[lca_tree.query(min(index[i], index[j]), max(index[i], index[j]) + 1)];
            int vi = tree.query(0, start[i] + 1);
            int vj = tree.query(0, start[j] + 1);
            cout << (vi ^ vj ^ e[lca]) << "\n";
        }
    }

    return 0;
}
