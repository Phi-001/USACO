#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    int n;
    long long k;
    cin >> n;
    cin >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    vector<int> size(n);

    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && a[r] - a[l] <= k) {
            r++;
        }

        size[l] = r - l;
    }

    vector<int> max_other(n + 1);
    max_other[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        max_other[i] = max(max_other[i + 1], size[i]);
    }

    int m = -1;
    for (int i = 0; i < n; i++) {
        int current = size[i] + max_other[i + size[i]];
        m = max(current, m);
    }

    cout << m << endl;

    return 0;
}
