#include <iostream>
#include <vector>
#include <set>

using namespace std;

void dfs_required(int v, vector<vector<int>> &fin, vector<int> &pinit, vector<set<int>> &required) {
    for (auto u : fin[v]) {
        dfs_required(u, fin, pinit, required);
        for (auto w : required[u])
            required[v].insert(pinit[w]);
    }
    required[v].insert(v);
}

void dfs_leftover(int v, vector<vector<int>> &fin, vector<vector<int>> &init, vector<set<int>> &required, vector<set<int>> &rejected) {
    set<int> child;
    for (auto u : fin[v])
        for (auto w : required[u])
            child.insert(w);

    for (auto k : fin[v]) {
        for (auto u : required[v]) {
            for (auto w : init[u]) {
                if (child.count(w) == 0) {
                    if (k > w) {
                        required[k].insert(w);
                        child.insert(w);
                    }
                }
            }
        }

        dfs_leftover(k, fin, init, required, rejected);

        for (auto w : rejected[k]) {
            child.erase(child.find(w));
            required[k].erase(required[k].find(w));
        }
    }

    for (auto u : required[v])
        for (auto w : init[u])
            if (child.count(w) == 0)
                rejected[v].insert(u);
}

void dfs_merge(int v, vector<vector<int>> &fin, vector<int> &pfin, vector<int> &pinit, vector<set<int>> &required) {
    set<int> remove;
    for (auto u : required[v])
        if (pfin[v] != -1 && required[pfin[v]].count(pinit[u]) == 0) remove.insert(u);

    for (auto u : remove)
        required[v].erase(required[v].find(u));

    for (auto u : required[v])
        if (u != v) cout << (u + 1) << " " << (v + 1) << "\n";

    for (auto u : fin[v])
        dfs_merge(u, fin, pfin, pinit, required);
}

int main() {
    int tt;
    cin >> tt;

    while (tt--) {
        int n;
        cin >> n;
        vector<vector<int>> init(n);
        vector<int> pinit(n, -1);

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            init[b].push_back(a);
            pinit[a] = b;
        }

        int root;
        for (int i = 0; i < n; i++)
            if (pinit[i] == -1)
                root = i;

        int m;
        cin >> m;
        vector<vector<int>> fin(n);
        vector<int> pfin(n, -1);

        for (int i = 0; i < m - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            fin[b].push_back(a);
            pfin[a] = b;
        }

        vector<set<int>> required(n);

        dfs_required(root, fin, pinit, required);

        vector<set<int>> rejected(n);
        dfs_leftover(root, fin, init, required, rejected);

        cout << n - m << "\n";
        dfs_merge(root, fin, pfin, pinit, required);
    }

    return 0;
}
