#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;

int main() {
    if (fopen("cownomics.in", "r")) {
        freopen("cownomics.in", "r", stdin);
        freopen("cownomics.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<vector<string>> str(2, vector<string>(n));

    for (int j = 0; j < 2; j++)
        for (int i = 0; i < n; i++)
            cin >> str[j][i];

    vector<long long> r(m);
    for (int i = 0; i < m; i++)
        r[i] = rand() % 1000000000;

    vector<vector<long long>> hash(2, vector<long long>(n));

    int ans = 1e9;

    int i = 0;
    int j = 0;
    bool worked = false;

    while (i < m && j < m) {
        if (!worked) {
            worked = true;
            set<int> seen;
            for (int k = 0; k < n; k++) seen.insert(hash[0][k] += r[j] * str[0][k][j]);
            for (int k = 0; k < n; k++) worked = worked & (seen.find(hash[1][k] += r[j] * str[1][k][j]) == seen.end());
            j++;
        } else {
            ans = min(ans, j - i);

            worked = true;
            set<int> seen;
            for (int k = 0; k < n; k++) seen.insert(hash[0][k] -= r[i] * str[0][k][i]);
            for (int k = 0; k < n; k++) worked = worked & (seen.find(hash[1][k] -= r[i] * str[1][k][i]) == seen.end());
            i++;
        }
    }

    cout << ans;

    return 0;
}
