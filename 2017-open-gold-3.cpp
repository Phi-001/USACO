#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    if (fopen("art2.in", "r")) {
        freopen("art2.in", "r", stdin);
        freopen("art2.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> painting(n + 2);
    painting[0] = 0;
    painting[n + 1] = 0;
    for (int i = 1; i <= n; i++)
        cin >> painting[i];

    vector<int> first(n + 1, 1e9);
    for (int i = 0; i < n + 2; i++)
        first[painting[i]] = min(first[painting[i]], i);

    vector<int> last(n + 1, -1);
    for (int i = 0; i < n + 2; i++)
        last[painting[i]] = max(last[painting[i]], i);

    vector<pair<int, int>> updates;

    for (int i = 0; i <= n; i++) {
        if (first[i] == 1e9 || last[i] == -1) continue;
        updates.push_back({ first[i], i });
        updates.push_back({ last[i], i + n + 1 });
    }

    sort(updates.begin(), updates.end());

    stack<int> s;

    int ans = -1;

    for (auto [ i, u ] : updates) {
        if (u >= n + 1) {
            if (s.top() != u - (n + 1)) {
                ans = 0;
                break;
            }
            s.pop();
        } else {
            s.push(u);
        }
        ans = max(ans, (int) s.size());
    }

    cout << ans - 1;

    return 0;
}
