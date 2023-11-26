#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    if (fopen("superbull.in", "r")) {
        freopen("superbull.in", "r", stdin);
        freopen("superbull.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> id(n);
    for (int i = 0; i < n; i++) cin >> id[i];

    vector<int> cost(n, -1);
    vector<bool> visited(n);

    long long ans = 0;
    int p = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cost[j] = max(cost[j], id[p] ^ id[j]);

        visited[p] = true;

        int mx = 0;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[j] > mx) {
                mx = cost[j];
                p = j;
            }
        }

        ans += mx;
    }

    cout << ans << "\n";

    return 0;
}
