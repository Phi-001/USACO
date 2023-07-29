#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

int main() {
    string s;
    cin >> s;

    set<int> unique;
    for (auto c : s) unique.insert(c);

    int n = unique.size();
    vector<vector<int>> adj(n, vector<int>(n));

    map<int, int> ord;
    for (auto c : unique) ord.insert({ c, ord.size() });

    for (int i = 1; i < s.size(); i++) {
        int a = ord[s[i - 1]];
        int b = ord[s[i]];
        adj[a][b]++;
    }

    vector<int> dp(1 << n, 1e9);
    dp[0] = 1;

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) continue;
            int a = 0;
            for (int k = 0; k < n; k++) {
                if (!(i & (1 << k))) continue;
                a += adj[k][j];
            }
            dp[i] = min(dp[i], dp[i ^ (1 << j)] + a);
        }
    }

    cout << dp[(1 << n) - 1];

    return 0;
}
