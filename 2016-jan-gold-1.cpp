#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

int bin_search(int lo, int hi, function<bool(int)> f) {
    while (lo < hi) {
        int mid = (hi - lo) / 2 + lo;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return hi;
}

int main() {
    if (fopen("angry.in", "r")) {
        freopen("angry.in", "r", stdin);
        freopen("angry.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> cows(n);

    for (int i = 0; i < n; i++)
        cin >> cows[i];

    sort(cows.begin(), cows.end());

    for (int i = 0; i < n; i++)
        cows[i] *= 2;

    auto f = [&](int R) {
        int lo = bin_search(0, 2e9, [&](int x) {
            int current = R;
            int last = x;
            for (int i = 0; i < n; i++) {
                if (cows[i] - last > current) {
                    if (i == 0) return false;
                    current -= 2;
                    if (cows[i] - cows[i - 1] > current) return false;
                    last = cows[i - 1];
                }
            }

            return true;
        });

        int hi = bin_search(0, 2e9, [&](int x) {
            int current = R;
            int last = x;
            for (int i = n - 1; i >= 0; i--) {
                if (last - cows[i] > current) {
                    if (i == n - 1) return true;
                    current -= 2;
                    if (cows[i + 1] - cows[i] > current) return true;
                    last = cows[i + 1];
                }
            }

            return false;
        });

        return lo < hi;
    };

    int ans = bin_search(0, 2e9, f);

    if (ans % 2 == 0) {
        cout << (ans / 2) << ".0";
    } else {
        cout << (ans / 2) << ".5";
    }

    return 0;
}
