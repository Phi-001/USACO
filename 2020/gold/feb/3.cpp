#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool check(vector<vector<int>> &nums, int k) {
    bool ok = true;

    for (auto &n : nums) {
        multiset<int> sizes;
        for (auto s : n) {
            int mod = s % k;
            if (mod != 0) {
                auto it = sizes.find(k - mod);
                if (it == sizes.end()) sizes.insert(mod);
                else sizes.erase(it);
            }
        }

        ok = ok && (sizes.size() < 2);
    }

    return ok;
}

int dfs_subtree(int v, int p, vector<vector<int>> &adj, vector<int> &subtree, vector<vector<int>> &nums) {
    subtree[v] = 1;

    for (auto u : adj[v]) {
        if (u != p) {
            int s = dfs_subtree(u, v, adj, subtree, nums);
            nums[v].push_back(s);
            subtree[v] += s;
        }
    }

    return subtree[v];
}

int main() {
    if (fopen("deleg.in", "r")) {
        freopen("deleg.in", "r", stdin);
        freopen("deleg.out", "w", stdout);
    }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> subtree(n);
    vector<vector<int>> nums(n);
    dfs_subtree(0, -1, adj, subtree, nums);

    for (int i = 1; i <= n - 1; i++) {
        if ((n - 1) % i != 0)
            cout << 0;
        else
            cout << check(nums, i);
    }

    return 0;
}
