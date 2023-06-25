#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <array>
#include <cstdio>

using namespace std;

int main() {
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<array<int, 5>> cows(n);

    for (int i = 0; i < n; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        array<int, 5> cow = { a, b, c, d, e };
        sort(cow.begin(), cow.end());
        cows[i] = cow;
    }

    map<array<int, 5>, int> count;
    long long ans = 0;

    for (int mask = 0; mask < 32; mask++) {
        int sign = __builtin_popcount(mask) % 2 ? -1 : 1;

        for (int j = 0; j < n; j++) {
            array<int, 5> c = {0};

            int l = 0;
            for (int k = 0; k < 5; k++) {
                if (mask & (1 << k)) c[l++] = cows[j][k];
            }

            ans += sign * count[c];
            count[c]++;
        }
    }

    cout << ans << "\n";

    return 0;
}
