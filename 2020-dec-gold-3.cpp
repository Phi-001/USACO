#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = n + 1;
    int eq = 0;

    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++)
        cin >> cows[i].first >> cows[i].second;

    auto solve = [&]() {
        sort(cows.begin(), cows.end());
        for (int a = 0; a < n; a++) {
            set<int> sorted_y;
            for (int b = a + 1 ; b < n; b++) {
                if (a < b - 1) sorted_y.insert(cows[b - 1].second);
                int len = cows[b].first - cows[a].first;
                int lo = max(cows[b].second, cows[a].second) - len;
                int hi = min(cows[b].second, cows[a].second);

                if (hi < lo) continue;

                vector<int> y(sorted_y.begin(), sorted_y.end());
                int l = 0;
                int r = -1;
                while (l < y.size() && lo >= y[l] + 1) l++;
                while (r + 1 < y.size() && lo >= y[r + 1] - len) r++;


                while (true) {
                    ans++;
                    int yl = min(cows[a].second, cows[b].second);
                    int yr = max(cows[a].second, cows[b].second);
                    if (l <= r) {
                        yl = min(yl, y[l]);
                        yr = max(yr, y[r]);
                    }

                    eq += (yr - yl) == len;

                    int leave_bottom = l < y.size() ? y[l] + 1 : 2e9;
                    int enter_top    = r + 1 < y.size() ? y[r + 1] - len : 2e9;
                    int change_y = min(leave_bottom, enter_top);
                    if (change_y > hi) break;
                    l += leave_bottom == change_y;
                    r += enter_top == change_y;
                }
            }
        }
    };

    solve();
    for (auto &p : cows) swap(p.first, p.second);
    solve();
    ans -= eq / 2;
    cout << ans;

    return 0;
}
