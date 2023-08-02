#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

int pow2(int i) {
    long long ans = 1;
    long long pow = 2;

    while (i > 0) {
        if (i & 1) {
            ans = ans * pow % mod;
        }

        pow = pow * pow % mod;
        i >>= 1;
    }

    return ans;
}

void dfs(int u, int p, vector<vector<int>> &adj, vector<vector<long long>> &ans) {
    for (auto v : adj[u])
        if (v != p)
            dfs(v, u, adj, ans);

    for (int i = 0; i < 3; i++) {
        for (auto v : adj[u]) {
            if (v == p) continue;

            long long c = 0;
            for (int j = 0; j < 3; j++) {
                if (j != i) {
                    c = (c + ans[v][j]) % mod;
                }
            }

            ans[u][i] = ans[u][i] * c % mod;
        }
    }
}

int main() {
    if (fopen("barnpainting.in", "r")) {
        freopen("barnpainting.in", "r", stdin);
        freopen("barnpainting.out", "w", stdout);
    }

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<long long>> ans(n, vector<long long>(3, 1));

    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        for (int j = 0; j < 3; j++) {
            if (j != b) ans[a][j] = 0;
        }
    }

    dfs(0, -1, adj, ans);

    long long out = 0;

    for (int i = 0; i < 3; i++)
        out = (out + ans[0][i]) % mod;

    cout << out;

    return 0;
}
