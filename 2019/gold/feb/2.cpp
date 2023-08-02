#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    if (fopen("dishes.in", "r")) {
        freopen("dishes.in", "r", stdin);
        freopen("dishes.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> stacks;
    vector<vector<int>> content;
    int clean = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] < clean) {
            cout << i;
            return 0;
        }
        int k = distance(stacks.begin(), lower_bound(stacks.begin(), stacks.end(), a[i]));
        if (k == stacks.size()) {
            stacks.push_back(a[i]);
            stacks.push_back(a[i]);
            content.push_back({ a[i] });
        } else {
            if (k % 2 == 0) {
                stacks[k] = a[i];
            } else {
                stacks[k - 1] = a[i];
                while (content[k / 2].back() < a[i]) {
                    clean = content[k / 2].back();
                    content[k / 2].pop_back();
                }
            }
            content[k / 2].push_back(a[i]);
        }
    }

    cout << n;

    return 0;
}
