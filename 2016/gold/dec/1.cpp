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
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    set<int> ecard;
    vector<int> elsie(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        c--;
        elsie[i] = c;
        ecard.insert(c);
    }

    vector<int> bessie;
    for (int i = 0; i < 2 * n; i++) {
        if (!ecard.count(i)) bessie.push_back(i);
    }

    set<int> low;
    for (int i = 0; i < n / 2; i++) {
        low.insert(bessie[i]);
    }

    set<int> high;
    for (int i = n / 2; i < n; i++) {
        high.insert(bessie[i]);
    }

    int wins = 0;
    for (int i = 0; i < n / 2; i++) {
        auto winning = high.lower_bound(elsie[i]);
        if (winning == high.end()) {
            high.erase(high.begin());
        } else {
            high.erase(winning);
            wins++;
        }
    }

    for (int i = n / 2; i < n; i++) {
        auto winning = low.lower_bound(elsie[i]);
        if (winning == low.begin()) {
            auto it = low.end();
            low.erase(--it);
        } else {
            low.erase(--winning);
            wins++;
        }
    }

    cout << wins;

    return 0;
}
