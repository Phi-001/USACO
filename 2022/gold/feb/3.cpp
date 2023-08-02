#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> p;
    int n;

    DSU (int size) {
        n = size;
        p.resize(n);
        fill(p.begin(), p.end(), -1);
    }

    int find(int a) {
        return p[a] < 0 ? a : p[a] = find(p[a]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (p[a] > p[b]) swap(a, b);

        p[a] += p[b];
        p[b] = a;

        return true;
    }
};

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> cows(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cows[i] = { x, y };
    }

    sort(cows.begin(), cows.end());

    vector<int> last_y(11, -1);
    vector<pair<long long, pair<int, int>>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 10; j++) {
            if (last_y[j] == -1) continue;
            long long dx = cows[last_y[j]].first - cows[i].first;
            long long dy = cows[last_y[j]].second - cows[i].second;
            long long d = dx * dx + dy * dy;
            edges.push_back({ d, { last_y[j], i } });
        }
        last_y[cows[i].second] = i;
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);

    long long ans = 0;

    for (auto [ d, e ] : edges) {
        auto [ a, b ] = e;
        if (dsu.unite(a, b)) ans += d;
    }

    cout << ans;

    return 0;
}
