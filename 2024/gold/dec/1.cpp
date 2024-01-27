#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> table1(n, vector<int>(n));
    vector<vector<int>> table2(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = n - 1; j > i; j--) {
            table1[i][j] = table2[i][j] = s[j - i - 1] == '1';
        }
    }

    int ans = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (table1[i][j] == 1) {
                ans++;

                for (int k = 0; k < n; k++)
                    table1[i][k] ^= table2[j][k];
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
