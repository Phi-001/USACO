#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<array<int, 4>> event(n);
    for (int i = 0; i < n; i++) {
        int q, t, x, k;
        cin >> q >> t >> x >> k;
        event[i] = { t - x, t + x, k, q };
    }

    sort(event.begin(), event.end());
    reverse(event.begin(), event.end());

    map<int, int> s;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        auto [ a, b, k, q ] = event[i];
        if (q == 1) {
            for (auto it = s.lower_bound(b); it != s.end();) {
                int m = min(k, it->second);
                it->second -= m;
                k -= m;
                ans += m;
                if (it->second == 0) it = s.erase(it);
                else break;
            }
        } else {
            s[b] += k;
        }
    }

    cout << ans;

    return 0;
}
