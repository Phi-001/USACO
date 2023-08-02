#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<vector<int>> dp(n, vector<int>(n, 1e9));
    vector<vector<int>> bottom(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
        bottom[i][i] = a[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            int a = j;
            int b = j + i;
            for (int k = a; k < b; k++) {
                int cost = dp[a][k] + dp[k + 1][b] - (bottom[a][k] == bottom[k + 1][b]);
                if (cost < dp[a][b]) {
                    dp[a][b] = cost;
                    bottom[a][b] = bottom[k + 1][b];
                }
            }
        }
    }

    cout << dp[0][n - 1];

    return 0;
}
