#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <stack>
#include <set>
#include <functional>

using namespace std;

int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    vector<int> weight(n);
    vector<int> talent(n);

    for (int i = 0; i < n; i++) {
        cin >> weight[i];
        cin >> talent[i];
    }

    vector<int> dp(w, -1);
    long long last_talent = -1;
    long long last_weight = 1;
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (last_talent != -1) {
            long long t = last_talent + talent[i];
            long long w = last_weight + weight[i];

            if (last_talent * w < t * last_weight) {
                last_weight = w;
                last_talent = t;
            }
        }

        for (int j = w - 1; j >= 0; j--) {
            if (dp[j] != -1) {
                if (j + weight[i] < w) {
                    dp[j + weight[i]] = max(dp[j + weight[i]], dp[j] + talent[i]);
                } else {
                    long long t = dp[j] + talent[i];
                    long long w = j + weight[i];

                    if (last_talent * w < t * last_weight) {
                        last_weight = w;
                        last_talent = t;
                    }
                }
            }
        }
    }

    cout << last_talent * 1000 / last_weight;

    return 0;
}
