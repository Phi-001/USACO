#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int main() {
    if (fopen("hayfeast.in", "r")) {
        freopen("hayfeast.in", "r", stdin);
        freopen("hayfeast.out", "w", stdout);
    }

    int n;
    long long m;

    cin >> n >> m;

    vector<int> f(n);
    vector<int> s(n);

    for (int i = 0; i < n; i++)
        cin >> f[i] >> s[i];

    int l = 0;
    int r = 0;

    multiset<int> ss;
    long long total = 0;

    int ans = 1e9;

    while (r <= n) {
        if (total < m) {
            total += f[r];
            ss.insert(s[r]);
            r++;
        } else {
            ans = min(ans, *ss.rbegin());
            total -= f[l];
            ss.erase(ss.find(s[l]));
            l++;
        }
    }

    cout << ans;

    return 0;
}
