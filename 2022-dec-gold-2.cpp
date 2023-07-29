#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> m(n);
    for (int i = 0; i < n; i++) cin >> m[i];

    vector<set<int>> visible(n);
    for (int x = 0; x < n; x++) {
        long long mdh = -1e9;
        long long mdx = 1;
        for (int j = x + 1; j < n; j++) {
            long long dx = j - x;
            long long dh = m[j] - m[x];

            if (dh * mdx >= mdh * dx) {
                mdh = dh;
                mdx = dx;
                visible[x].insert(j);
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, u;
        cin >> x >> u;
        x--;

        m[x] += u;

        for (int j = 0; j < x; j++) {
            long long dh = m[x] - m[j];
            long long dx = x - j;

            for (auto it = visible[j].upper_bound(x); it != visible[j].end() && dh * (*it - j) > (m[*it] - m[j]) * dx;)
                it = visible[j].erase(it);

            auto it = visible[j].lower_bound(x);

            if (it == visible[j].begin()) visible[j].insert(x);
            else {
                it--;
                if (dh * (*it - j) >= (m[*it] - m[j]) * dx) visible[j].insert(x);
            }
        }

        visible[x].clear();
        long long mdh = -1e9;
        long long mdx = 1;
        for (int j = x + 1; j < n; j++) {
            long long dx = j - x;
            long long dh = m[j] - m[x];

            if (dh * mdx >= mdh * dx) {
                mdh = dh;
                mdx = dx;
                visible[x].insert(j);
            }
        }

        int ans = 0;
        for (int j = 0; j < n; j++) {
            ans += visible[j].size();
        }

        cout << ans << "\n";
    }

    return 0;
}
