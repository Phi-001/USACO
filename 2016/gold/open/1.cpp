#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    if (fopen("split.in", "r")) {
        freopen("split.in", "r", stdin);
        freopen("split.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<pair<int, int>> cows(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cows[i] = { x, y };
    }

    auto by_x = [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; };
    auto by_y = [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; };

    sort(cows.begin(), cows.end(), by_x);

    vector<long long> xf(n);
    int minimum = 1e9;
    int maximum = -1e9;
    for (int i = 0; i < n; i++) {
        maximum = max(maximum, cows[i].second);
        minimum = min(minimum, cows[i].second);
        xf[i] = maximum - minimum;
    }

    minimum = 1e9;
    maximum = -1e9;
    vector<long long> xb(n);
    for (int i = n - 1; i >= 0; i--) {
        maximum = max(maximum, cows[i].second);
        minimum = min(minimum, cows[i].second);
        xb[i] = maximum - minimum;
    }

    long long ans = 1e18;
    for (int i = 0; i < n - 1; i++) {
        ans = min(ans, (cows[i].first - cows[0].first) * xf[i] + (cows[n - 1].first - cows[i + 1].first) * xb[i + 1]);
    }

    sort(cows.begin(), cows.end(), by_y);

    vector<long long> yf(n);
    minimum = 1e9;
    maximum = -1e9;
    for (int i = 0; i < n; i++) {
        maximum = max(maximum, cows[i].first);
        minimum = min(minimum, cows[i].first);
        yf[i] = maximum - minimum;
    }

    minimum = 1e9;
    maximum = -1e9;
    vector<long long> yb(n);
    for (int i = n - 1; i >= 0; i--) {
        maximum = max(maximum, cows[i].first);
        minimum = min(minimum, cows[i].first);
        yb[i] = maximum - minimum;
    }

    for (int i = 0; i < n - 1; i++) {
        ans = min(ans, (cows[i].second - cows[0].second) * yf[i] + (cows[n - 1].second - cows[i + 1].second) * yb[i + 1]);
    }

    cout << (xb[0] * yb[0]) - ans << "\n";

    return 0;
}
