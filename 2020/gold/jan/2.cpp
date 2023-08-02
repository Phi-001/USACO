#include <iostream>
#include <vector>

using namespace std;

int main() {
    if (fopen("threesum.in", "r")) {
        freopen("threesum.in", "r", stdin);
        freopen("threesum.out", "w", stdout);
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<long long>> ans(n, vector<long long>(n));
    vector<int> count(2e6 + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] + a[j] >= -1e6 && a[i] + a[j] <= 1e6)
                ans[i][j] = count[-a[i] - a[j] + 1e6];
            count[a[j] + 1e6]++;
        }

        for (int j = i + 1; j < n; j++)
            count[a[j] + 1e6]--;
    }

    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            ans[i][j] += ans[i + 1][j] + ans[i][j - 1] - ans[i + 1][j - 1];

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        cout << ans[l][r] << "\n";
    }

    return 0;
}
