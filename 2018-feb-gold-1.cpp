#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <array>
#include <cstdio>
#include <queue>
#include <set>

using namespace std;

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, b;
    cin >> n >> b;

    set<pair<int, int>> snow;
    for (int i = 0; i < n; i++) {
        int f;
        cin >> f;
        snow.insert({ f, i });
    }

    vector<array<int, 3>> boots(b);
    for (int i = 0; i < b; i++) {
        int s, d;
        cin >> s >> d;
        boots[i] = { s, d, i };
    }

    sort(boots.begin(), boots.end());

    // holds places where the boots can step on
    set<int> ends;
    ends.insert(0);
    ends.insert(n - 1);

    snow.erase({ 0, 0 });
    snow.erase({ 0, n - 1 });

    // the sizes of each interval between each place where
    // boots can step on
    multiset<int> intervals;
    intervals.insert(n - 2);

    vector<bool> ans(b);

    for (int i = 0; i < b; i++) {
        while (!snow.empty() && (*snow.begin()).first <= boots[i][0]) {
            auto [ f, i ] = *snow.begin();
            snow.erase({ f, i });

            auto it = ends.lower_bound(i);
            int r = *it;
            int l = *(--it);

            intervals.erase(intervals.find(r - l - 1));
            intervals.insert(i - l - 1);
            intervals.insert(r - i - 1);

            ends.insert(i);
        }

        ans[boots[i][2]] = *intervals.rbegin() < boots[i][1];
    }

    for (int i = 0; i < b; i++) {
        cout << (int) ans[i] << "\n";
    }

    return 0;
}
