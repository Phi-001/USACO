#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int v, vector<vector<int>> &child, vector<int> &x, vector<int> &h, int &i) {
    reverse(child[v].begin(), child[v].end());

    for (auto u : child[v]) {
        x[u] = --i;
        h[u] = h[v] + 1;
        dfs(u, child, x, h, i);
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> child(n + 1);
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        child[j].push_back(i);
    }

    vector<int> x(n + 1);
    vector<int> h(n + 1);
    int k = n + 1;
    int i = k - 1;
    x[n] = i;
    dfs(n, child, x, h, i);

    int mxh = -1;
    for (int i = 0; i <= n; i++)
        mxh = max(mxh, h[i]);

    cout << k << "\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] + (long long) k * (mxh - h[i]) << "\n";
    }
}
