#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main() {
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);

    int n, l;
    cin >> n >> l;

    vector<pair<int, vector<int>>> movie(n);
    for (int i = 0; i < n; i++) {
        cin >> movie[i].first;
        int c;
        cin >> c;
        movie[i].second.resize(c);
        for (int j = 0; j < c; j++) {
            cin >> movie[i].second[j];
        }
    }

    int ans = 1e9;

    vector<int> dp(1 << n, -1);
    dp[0] = 0;

    for (int s = 1; s < (1 << n); s++) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                count++;

                auto it = upper_bound(movie[i].second.begin(), movie[i].second.end(), dp[s ^ (1 << i)]);

                if (it == movie[i].second.begin()) continue;

                int lower = *(--it);

                if (lower + movie[i].first >= dp[s ^ (1 << i)]) {
                    dp[s] = max(dp[s], lower + movie[i].first);
                }
            }
        }

        if (dp[s] >= l) {
            ans = min(ans, count);
        }
    }

    if (ans == 1e9) cout << -1;
    else cout << ans;

    return 0;
}
