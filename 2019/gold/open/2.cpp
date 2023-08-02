#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

using namespace std;

int dist(int a, int b) {
    return (2019201913LL * a + 2019201949LL * b) % 2019201997LL;
}

int main() {
    if (fopen("walk.in", "r")) {
        freopen("walk.in", "r", stdin);
        freopen("walk.out", "w", stdout);
    }

    int n, k;
    cin >> n >> k;

    vector<int> mst;

    vector<int> d(n + 1);
    for (int i = 2; i <= n; i++) d[i] = dist(1, i);

    for (int i = 2; i <= n; i++) {
        int closest = INT_MAX;
        int v;

        for (int j = 1; j <= n; j++) {
            if (d[j] != 0) {
                closest = min(closest, d[j]);
                v = j;
            }
        }

        mst.push_back(closest);

        for (int j = 1; j <= n; j++) {
            d[j] = min(d[j], dist(min(j, v), max(j, v)));
        }

        d[v] = 0;
    }

    sort(mst.begin(), mst.end());

    cout << mst[n - k];

    return 0;
}
