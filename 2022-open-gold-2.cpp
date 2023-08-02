#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

const int mod = 1e9 + 7;
struct Mint {
    int v;

    Mint () { v = 0; }
    Mint (int a) { v = (a + mod) % mod; }
    Mint& operator+=(const Mint &rhs) { this->v = (this->v + rhs.v) % mod; return *this; }
    friend Mint operator+(Mint lhs, const Mint &rhs) { lhs += rhs; return lhs; }
};

int main() {
    int tt;
    cin >> tt;

    while (tt--) {
        int n;
        cin >> n;
        string s1, s2;
        cin >> s1 >> s2;

        auto read = [&](string s) {
            vector<bool> t;
            for (int i = 0; i < n; i++) {
                if (s[i] == '1') continue;
                if (s[i] == '0') t.clear();
                t.push_back(s[i] == '+');
            }
            return t;
        };

        vector<bool> t1 = read(s1);
        vector<bool> t2 = read(s2);

        vector<vector<array<Mint, 2>>> dp(t1.size() + 1, vector<array<Mint, 2>>(t2.size() + 1));
        dp[0][0][0] = 1;

        Mint ans = 0;

        for (int i = 0; i <= t1.size(); i++) {
            for (int j = 0; j <= t2.size(); j++) {
                for (int k = 0; k < 2; k++) {
                    Mint v = dp[i][j][k];
                    if (v.v == 0) continue;
                    if (i == t1.size() && j == t2.size()) {
                        ans += v;
                    } else {
                        if (j + 1 <= t2.size())
                            dp[i][j + 1][1] += v;
                        if (k == 0 && i + 1 <= t1.size())
                            dp[i + 1][j][0] += v;
                        else if (i < t1.size() && t2[j - 1] != t1[i])
                            dp[i + 1][j][0] += v;
                    }
                }
            }
        }

        cout << ans.v << "\n";
    }

    return 0;
}
