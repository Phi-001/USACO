#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool in(int a, pair<int, int> s) {
    return s.first <= a && a <= s.second;
}

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<pair<long long, pair<int, int>>> sums;

    for (int i = 0; i < n; i++) {
        long long psum = 0;
        for (int j = i; j < n; j++) {
            psum += a[j];
            sums.push_back({ psum, { i, j } });
        }
    }

    sort(sums.begin(), sums.end());

    for (int i = 0; i < n; i++) {
        long long ans = 1e18;
        for (int j = 1; j < n * (n + 1) / 2; j++)
            if (in(i, sums[j - 1].second) ^ in(i, sums[j].second))
                ans = min(ans, abs(sums[j - 1].first - sums[j].first));

        cout << ans << "\n";
    }

    return 0;
}
