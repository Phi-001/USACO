#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.size();

    vector<int> cost(n);
    for (int i = 0; i < n; i++) cin >> cost[i];

    vector<array<array<int, 2>, 6>> dp(n + 1);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 6; j++)
            dp[i][j] = { (int) -1e9, (int) 1e9 };

    dp[0][0] = { 0, 0 };

    string target = "bessie";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            auto [ b, c ] = dp[i][j];
            if (s[i] == target[j]) {
                auto [ b2, c2 ] = dp[i + 1][(j + 1) % 6];
                int bn = j == 5 ? b + 1 : b;

                if (bn == b2)
                    dp[i + 1][(j + 1) % 6] = { b2, min(c, c2) };
                else if (bn > b2)
                    dp[i + 1][(j + 1) % 6] = { bn, c };
            }

            auto [ b2, c2 ] = dp[i + 1][j];
            int cn = j == 0 ? c : c + cost[i];

            if (b == b2)
                dp[i + 1][j] = { b, min(cn, c2) };
            else if (b > b2)
                dp[i + 1][j] = { b, cn };
        }
    }

    auto [ ans, tc ] = dp[n][0];

    cout << ans << "\n";
    cout << tc;

    return 0;
}
