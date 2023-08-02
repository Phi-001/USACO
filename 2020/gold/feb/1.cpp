#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    if (fopen("timeline.in", "r")) {
        freopen("timeline.in", "r", stdin);
        freopen("timeline.out", "w", stdout);
    }

    int n, m, c;
    cin >> n >> m >> c;

    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    vector<vector<pair<int, int>>> adj(n);
    vector<int> in(n);

    for (int i = 0; i < c; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        a--; b--;

        adj[a].push_back({ b, x });
        in[b]++;
    }

    queue<int> q;

    for (int i = 0; i < n; i++)
        if (in[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [ v, x ] : adj[u]) {
            in[v]--;
            s[v] = max(s[v], s[u] + x);
            if (in[v] == 0) q.push(v);
        }
    }

    for (int i = 0; i < n; i++)
        cout << s[i] << "\n";

    return 0;
}
