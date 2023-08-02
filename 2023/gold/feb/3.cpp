#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

struct Mint {
    const int mod = 1e9 + 7;
    int v;

    Mint () { v = 0; }
    Mint (long long _v) { v = (_v + mod) % mod; }
    Mint& operator+=(const Mint &rhs) { this->v = (this->v + rhs.v) % mod; return *this; }
    Mint& operator-=(const Mint &rhs) { this->v = (this->v - rhs.v + mod) % mod; return *this; }
    friend Mint operator+(Mint lhs, const Mint &rhs) { lhs += rhs; return lhs; }
    friend Mint operator-(Mint lhs, const Mint &rhs) { lhs -= rhs; return lhs; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long a, b;
    cin >> n >> a >> b;

    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    auto LessEq = [&](long long a, vector<int> &d) {
        int n = d.size();

        vector<int> dt(18);
        int c = 17;
        while (a != 0) {
            dt[c] = a % 10;
            a /= 10;
            c--;
        }

        vector<vector<Mint>> ans(n, vector<Mint>(n));

        for (int i = 0; i < n; i++) {
            array<array<Mint, 18>, 18> eq;
            array<array<Mint, 18>, 18> less;
            array<array<Mint, 18>, 18> more;
            for (int j = i; j < n; j++) {
                for (int x = 17; x >= 0; x--) {
                    for (int r = x; r < 18; r++) {
                        int l = r - x;

                        if (l == r) {
                            eq[l][r] += 2 * (d[j] == dt[r]);
                            less[l][r] += 2 * (d[j] < dt[r]);
                            more[l][r] += 2 * (d[j] > dt[r]);
                            continue;
                        }

                        // add to bottom
                        if (r != 0) {
                            if (d[j] == dt[r]) eq[l][r] += eq[l][r - 1];
                            if (d[j] < dt[r]) less[l][r] += eq[l][r - 1];
                            if (d[j] > dt[r]) more[l][r] += eq[l][r - 1];

                            less[l][r] += less[l][r - 1];
                            more[l][r] += more[l][r - 1];
                        }

                        // add to top
                        if (l != 17) {
                            if (d[j] == dt[l]) {
                                eq[l][r] += eq[l + 1][r];
                                less[l][r] += less[l + 1][r];
                                more[l][r] += more[l + 1][r];
                            }

                            if (d[j] < dt[l]) {
                                less[l][r] += eq[l + 1][r];
                                less[l][r] += less[l + 1][r];
                                less[l][r] += more[l + 1][r];
                            }

                            if (d[j] > dt[l]) {
                                more[l][r] += eq[l + 1][r];
                                more[l][r] += less[l + 1][r];
                                more[l][r] += more[l + 1][r];
                            }
                        }
                    }
                }

                ans[i][j] += less[c + 1][17] + eq[c + 1][17];
                for (int k = c + 2; k <= 17; k++) {
                    ans[i][j] += eq[k][17];
                    ans[i][j] += less[k][17];
                    ans[i][j] += more[k][17];
                }
            }
        }

        return ans;
    };

    vector<vector<Mint>> la = LessEq(a - 1, d);
    vector<vector<Mint>> lb = LessEq(b, d);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        cout << (lb[l][r] - la[l][r]).v << "\n";
    }

    return 0;
}
