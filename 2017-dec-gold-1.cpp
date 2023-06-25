#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <array>

using namespace std;

int main() {
    if (fopen("piepie.in", "r")) {
        freopen("piepie.in", "r", stdin);
        freopen("piepie.out", "w", stdout);
    }

    int n, d;
    cin >> n >> d;

    // sorted by elsie
    multimap<int, array<int, 2>> bessie;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        bessie.insert({ b, { a, i } });
    }

    // sorted by bessie
    multimap<int, int> elsie;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        elsie.insert({ a, b });
    }

    queue<array<int, 3>> q;

    while (bessie.find(0) != bessie.end()) {
        q.push({ bessie.find(0)->second[0], bessie.find(0)->second[1], 1 });
        bessie.erase(bessie.find(0));
    }

    while (elsie.find(0) != elsie.end()) {
        q.push({ elsie.find(0)->second, -1, 1 });
        elsie.erase(elsie.find(0));
    }

    vector<int> ans(n, -1);

    while (!q.empty()) {
        auto [ t, i, e ] = q.front();
        q.pop();
        if (i == -1) {
            for (auto it = bessie.lower_bound(t - d); it != bessie.upper_bound(t); ) {
                q.push({ it->second[0], it->second[1], e + 1 });
                it = bessie.erase(it);
            }
        } else {
            ans[i] = e;
            for (auto it = elsie.lower_bound(t - d); it != elsie.upper_bound(t); ) {
                q.push({ it->second, -1, e + 1 });
                it = elsie.erase(it);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
