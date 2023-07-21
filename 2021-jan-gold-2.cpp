#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        int bi;
        cin >> bi;
        b[i] = bi - 1;
    }

    vector<vector<bool>> s(k, vector<bool>(k));

    for (int i = 0; i < k; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < k; j++)
            s[i][j] = str[j] == '1';
    }

    vector<int> ans(n, 1e9);
    ans[0] = 0;

    for (int i = 0; i < k; i++) {
        vector<int> forward(k, -1);
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++)
                if (forward[l] != -1 && s[l][b[j]])
                    ans[j] = min(ans[j], ans[forward[l]] + (j - forward[l]));
            if (forward[b[j]] == -1 || ans[j] - j < ans[forward[b[j]]] - forward[b[j]]) forward[b[j]] = j;
        }

        vector<int> backward(k, -1);
        for (int j = n - 1; j >= 0; j--) {
            for (int l = 0; l < k; l++)
                if (backward[l] != -1 && s[l][b[j]])
                    ans[j] = min(ans[j], ans[backward[l]] + (backward[l] - j));
            if (backward[b[j]] == -1 || ans[j] + j < ans[backward[b[j]]] + backward[b[j]]) backward[b[j]] = j;
        }
    }

    if (ans[n - 1] == 1e9) cout << -1;
    else cout << ans[n - 1];

    return 0;
}
