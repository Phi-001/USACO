#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <array>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n);
    vector<int> indeg(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long l;
        cin >> a >> b >> l;
        a--; b--;
        adj[b].push_back({ a, l });
        indeg[a]++;
    }

    // dist, lable, counter, sum, vert
    priority_queue<array<long long, 5>> q;
    vector<pair<int, long long>> ans(n);

    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push({ 0, 0, 0, 0, i });

    int counter = 0;

    while (!q.empty()) {
        auto a = q.top();
        q.pop();

        int d = -a[0];
        int v = a[4];
        long long s = a[3];

        indeg[v]--;
        if (indeg[v] > 0) continue;

        ans[v] = { d, s };

        for (auto [ w, l ] : adj[v]) {
            q.push({ -(d + 1), l, -counter, s + l, w });
            counter++;
        }
    }

    for (int i = 0; i < n; i++)
        cout << ans[i].first << " " << ans[i].second << "\n";

    return 0;
}
