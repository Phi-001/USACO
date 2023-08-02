#include <iostream>
#include <vector>
#include <array>

using namespace std;

const int mod = 1e9 + 7;
struct Mint {
    int v;

    Mint () : v(0) {}
    Mint (int a) { v = (a + mod) % mod; }
    Mint& operator+=(const Mint& rhs) { this->v = (this->v + rhs.v) % mod; return *this; }
    friend Mint operator+(Mint lhs, const Mint& rhs) { lhs += rhs; return lhs; }
};

int main() {
    string s;
    cin >> s;

    int n = s.size();

    vector<array<array<array<Mint, 4>, 4>, 4>> dp(n + 1);
    vector<array<array<Mint, 4>, 4>> ans(n + 1);

    auto index = [](char a) {
        if (a == 'A') return 0;
        if (a == 'T') return 1;
        if (a == 'G') return 2;
        if (a == 'C') return 3;
        return 4;
    };

    for (int i = 0; i < 4; i++)
        ans[0][0][i] = 1;

    for (int i = 1; i <= n; i++) {
        int c = index(s[i - 1]);

        for (int a = 0; a < 4; a++) {
            if (c != 4 && c != a) continue;
            for (int p = 0; p < 4; p++) {
                ans[i][a][a] += ans[i - 1][p][a];

                if (p != a) {
                    for (int j = 0; j < 4; j++) {
                        for (int k = 0; k < 4; k++)
                            dp[i][a][j][k] += dp[i - 1][p][j][k];
                        ans[i][a][j] += dp[i - 1][p][a][j];
                    }
                }

                for (int j = 0; j < 4; j++)
                    dp[i][a][j][a] += ans[i - 1][p][j];
            }
        }
    }


    Mint out = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out += ans[n][i][j];

    cout << out.v;

    return 0;
}
