#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<bool> possible(vector<int> &c, vector<int> &p, vector<vector<int>> &adj, int n, bool back, vector<bool> last) {
    vector<bool> has(n + 1);
    vector<vector<int>> color(n + 1);
    vector<bool> visit(n);
    vector<bool> can(n);
    queue<int> q;

    q.push(0);
    visit[0] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        can[v] = true;

        if (!has[p[v]]) {
            for (auto u : color[p[v]]) {
                q.push(u);
            }
            has[p[v]] = true;
        }

        for (auto u : adj[v]) {
            if (!visit[u]) {
                if (has[c[u]]) q.push(u);
                else if (back && c[u] == p[u] && last[u]) q.push(u);
                else color[c[u]].push_back(u);
                visit[u] = true;
            }
        }
    }

    return can;
}

int main() {
    int tt;
    cin >> tt;

    while (tt--) {
        int n, m;
        cin >> n >> m;

        vector<int> c(n);
        for (int i = 0; i < n; i++) cin >> c[i];

        vector<int> s(n);
        for (int i = 0; i < n; i++) cin >> s[i];

        vector<int> f(n);
        for (int i = 0; i < n; i++) cin >> f[i];

        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        bool ans = true;

        vector<bool> start = possible(c, s, adj, n, false, {});
        vector<bool> end = possible(c, f, adj, n, true, start);

        for (int i = 0; i < n; i++) {
            ans = ans && (start[i] ? end[i] : s[i] == f[i]);
        }

        if (ans) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
