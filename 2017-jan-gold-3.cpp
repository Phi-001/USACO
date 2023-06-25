#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdio>
#include <array>
#include <map>

using namespace std;

vector<int> dx = { 1, 0, -1, 0 };
vector<int> dy = { 0, 1, 0, -1 };

int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);

    int n;
    cin >> n;

    vector<string> barn(n);

    for (int i = 0; i < n; i++) cin >> barn[i];

    auto inside = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n && barn[n - y - 1][x] == 'E';
    };

    auto index = [&](array<array<int, 3>, 2> a) {
        return (a[0][0] * n * 4 + a[0][1] * 4 + a[0][2]) * n * n * 4 + (a[1][0] * n * 4 + a[1][1] * 4 + a[1][2]);
    };

    vector<int> depth(n * n * n * n * 16);

    queue<array<array<int, 3>, 2>> visit;
    array<array<int, 3>, 2> start = {{ {{ 0, 0, 0 }}, {{ 0, 0, 1 }} }};
    visit.push(start);

    depth[index(start)] = 1;

    while (!visit.empty()) {
        array<array<int, 3>, 2> v = visit.front();
        visit.pop();

        array<array<int, 3>, 2> r1 = v;
        array<array<int, 3>, 2> r2 = v;

        for (int i = 0; i < 2; i++) {
            r1[i][2] = (r1[i][2] + 1) % 4;
            r2[i][2] = (r2[i][2] + 3) % 4;
        }

        array<array<int, 3>, 2> f = v;

        for (int i = 0; i < 2; i++) {
            int nx = v[i][0] + dx[v[i][2]];
            int ny = v[i][1] + dy[v[i][2]];
            if (!(v[i][0] == n - 1 && v[i][1] == n - 1) && inside(nx, ny)) {
                f[i] = { nx, ny, v[i][2] };
            }
        }

        array<array<array<int, 3>, 2>, 3> opt = { f, r1, r2 };

        for (int i = 0; i < 3; i++) {
            if (depth[index(opt[i])] == 0) {
                depth[index(opt[i])] = depth[index(v)] + 1;
                visit.push(opt[i]);
            }
        }
    }

    int ans = 1e9;

    for (int i = 0; i < 4; i++) {
        array<array<int, 3>, 2> end = {{ {{ n - 1, n - 1, i }}, {{ n - 1, n - 1, (i + 1) % 4 }} }};
        ans = min(ans, depth[index(end)]);
    }

    cout << ans - 1;

    return 0;
}
