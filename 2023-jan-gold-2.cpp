#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t, n;
    cin >> t >> n;

    auto Cycle = [&](int i) {
        return i >> 1 | (i & 1) << (n - 1);
    };

    vector<int> rep(1 << n, -1);

    for (int i = 0; i < (1 << n); i++) {
        int j = i;
        while (rep[j] == -1) {
            rep[j] = i;
            j = Cycle(j);
        }
    }

    vector<vector<bool>> dp(3 * n + 1, vector<bool>(1 << n));
    dp[0][0] = true;

    int k = 0;
    for (int i = 1; i <= 3 * n; i++) {
        k ^= 1 << ((i - 1) % n);
        for (int mask = 0; mask < (1 << n); mask++)
            if (dp[i - 1][rep[mask]])
                dp[i][rep[mask ^ k]] = true;
    }

    auto Extract = [](string s) {
        int k = 0;
        for (int i = 0; i < s.size(); i++)
            k |= (s[i] == '1') << (s.size() - i - 1);
        return k;
    };

    for (int i = 0; i < t; i++) {
        string l, s;
        cin >> l >> s;
        int swtch = Extract(s);
        int light = Extract(l);

        for (int j = 0; j <= 3 * n; j++) {
            if (dp[j][rep[light]]) {
                cout << j << "\n";
                break;
            }
            light ^= swtch;
            swtch = Cycle(swtch);
        }
    }
}
