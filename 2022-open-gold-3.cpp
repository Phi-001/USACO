#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

struct Interval {
    long long l = LLONG_MAX;
    long long r = LLONG_MIN;

    Interval unite(Interval b) {
        return { min(l, b.l), max(r, b.r) };
    }

    long long closest(long long a) {
        return max(min(a, r), l);
    }

    Interval flip() {
        return { r, l };
    }

    bool empty() {
        return l > r;
    }
};

void dfs2(int v, int p, long long k, vector<vector<int>> &adj, vector<long long> &s, vector<Interval> &bound) {
    s[v] = bound[v].closest(k);
    for (auto u: adj[v]) {
        if (u != p) {
            if (s[u] == -1) dfs2(u, v, k, adj, s, bound);
        }
    }
}

void dfs1(int v, int p, vector<vector<int>> &adj, vector<Interval> &dp, vector<Interval> &bound, vector<long long> &ans, vector<long long> &s) {
    for (auto u : adj[v]) {
        if (u != p) {
            dfs1(u, v, adj, dp, bound, ans, s);
            dp[v] = dp[v].unite(dp[u]);
            ans[v] = max(ans[v], ans[u]);
        }
    }

    dp[v] = dp[v].unite(bound[v].flip());

    if (!dp[v].empty()) {
        s[v] = bound[v].closest((dp[v].l + dp[v].r) / 2);
        ans[v] = max(max(s[v] - dp[v].l, dp[v].r - s[v]), ans[v]);
        dfs2(v, p, s[v], adj, s, bound);
    }
}

int main() {
    int tt;
    cin >> tt;

    int b;
    cin >> b;

    while (tt--) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;

            adj[p].push_back(i);
            adj[i].push_back(p);
        }

        vector<Interval> bound(n);

        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;

            bound[i] = { l, r };
        }

        vector<Interval> dp(n);
        vector<long long> ans(n);
        vector<long long> s(n, -1);

        dfs1(0, -1, adj, dp, bound, ans, s);

        cout << ans[0] << "\n";

        if (b == 1) {
            for (int i = 0; i < n; i++) {
                cout << s[i] << " \n"[i == n - 1];
            }
        }
    }

    return 0;
}
