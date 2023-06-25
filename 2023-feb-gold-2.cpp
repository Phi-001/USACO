#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <algorithm>
#include <cmath>

using namespace std;

struct SubTree {
    long long a;
    int t;
    int v;

    friend bool operator<(const SubTree &l, const SubTree &r) {
        return l.t * r.a < l.a * r.t;
    }
};

void dfs(vector<vector<int>> &adj, vector<array<int, 2>> &dp1, vector<array<long long, 2>> &dp2, vector<long long> &dp3, int v, int p, vector<int> &map) {
    for (auto u : adj[v]) {
        if (u != p) dfs(adj, dp1, dp2, dp3, u, v, map);
    }

    vector<SubTree> childs;
    for (auto u : adj[v]) {
        if (u != p) {
            dp1[v][0] += dp1[u][0] + 2;
            dp2[v][0] += dp2[u][0];
            dp3[v] += dp3[u];
            childs.push_back({ dp3[u], dp1[u][0] + 2, u });
        }
    }

    if (childs.size() == 0) return;

    sort(childs.begin(), childs.end());

    int t = 1;
    for (int i = 0; i < childs.size(); i++) {
        auto e = childs[i];
        map[e.v] = i;
        dp2[v][0] += t * e.a;
        t += e.t;
    }

    vector<long long> ssuma(childs.size() + 1);
    ssuma[childs.size()] = 0;
    for (int i = childs.size() - 1; i >= 0; i--) ssuma[i] = ssuma[i + 1] + childs[i].a;

    vector<long long> psumt(childs.size() + 1);
    psumt[0] = 1;
    for (int i = 1; i <= childs.size(); i++) psumt[i] = psumt[i - 1] + childs[i - 1].t;

    dp1[v][1] = dp1[v][0];
    dp2[v][1] = 1e18;
    for (auto u : adj[v]) {
        if (u != p) {
            int c = dp1[v][0] - dp1[u][0] - 1 + dp1[u][1];
            long long subp = psumt[map[u]] * dp3[u];
            long long suba = ssuma[map[u] + 1] * (dp1[u][0] + 2);
            long long c2 = dp2[v][0] - suba - subp +
                    (psumt[childs.size()] - dp1[u][0] - 2) * dp3[u]
                    - dp2[u][0] + dp2[u][1];

            if (dp1[v][1] > c) {
                dp1[v][1] = c;
                dp2[v][1] = c2;
            }

            if (dp1[v][1] == c) {
                dp2[v][1] = min(dp2[v][1], c2);
            }
        }
    }
}

int main() {
    int n, t;
    cin >> n >> t;

    vector<long long> dp3(n);
    vector<vector<int>> adj(n);

    for (int i = 1; i < n; i++) {
        int p, a;
        cin >> p >> a;
        p--;
        adj[i].push_back(p);
        adj[p].push_back(i);
        dp3[i] = a;
    }

    vector<array<int, 2>> dp1(n);
    vector<array<long long, 2>> dp2(n);
    vector<int> map(n);

    dfs(adj, dp1, dp2, dp3, 0, -1, map);

    cout << dp1[0][t] << " " << dp2[0][t];

    return 0;
}
