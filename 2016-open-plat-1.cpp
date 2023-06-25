#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

int main() {
    if (fopen("262144.in", "r")) {
        freopen("262144.in", "r", stdin);
        freopen("262144.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<vector<int>> a;

    a.push_back(vector<int>(n));

    for (int i = 0; i < n; i++) {
        cin >> a[0][i];
    }

    int ans = -1;

    for (int i = 1; i <= 60; i++) {
        vector<vector<int>> c;
        c.push_back({});
        for (auto s : a) {
            if (s.size() == 0) continue;
            if (s.size() == 1) ans = max(ans, s[0]);

            vector<pair<int, int>> split;
            int l = 0;
            int r = -1;

            for (int j = 0; j < s.size(); j++) {
                if (s[j] == i) r++;
                else {
                    if (l <= r) split.push_back({ l, r });
                    l = j + 1;
                    r = j;
                }
            }

            if (l <= r) split.push_back({ l, r });

            int p = 0;
            for (int j = 0; j < s.size(); j++) {
                int push = s[j] == i ? i + 1 : s[j];
                if (p < split.size() && (2 * j) == (split[p].first + split[p].second)) {
                    c.push_back({});
                    p++;
                } else if (p < split.size() && (2 * j + 1) == (split[p].first + split[p].second)) {
                    (*c.rbegin()).push_back(push);
                    j = split[p].second;
                    p++;
                } else {
                    (*c.rbegin()).push_back(push);
                }
            }

            c.push_back({});
        }

        a = c;
    }

    cout << ans;

    return 0;
}
