#include <iostream>
#include <vector>

using namespace std;

bool solve(int n, int m) {
    vector<vector<int>> data(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;

        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            c--;
            data[i].push_back(c);
        }
    }

    vector<int> status(n, 0);
    vector<vector<int>> last(n);
    vector<int> order(n);

    for (auto &d : data) {
        vector<int> s;
        vector<bool> seen(n);

        int p = -1;

        for (int j = 0; j < d.size(); j++) {
            int c = d[j];

            if (seen[c]) {
                if (s.back() != c) return false;
                s.pop_back();
            } else {
                if (status[c] == 2) return false;
                if (status[c] == 1 && last[c].size() != s.size()) return false;
                for (int k = 0; k < s.size(); k++) {
                    if (status[c] == 0) last[c].push_back(s[k]);
                    else if (s[k] != last[c][k]) return false;
                }

                s.push_back(c);
                seen[c] = true;

                if (status[c] == 1) {
                    if (p > order[c]) return false;
                    p = order[c];
                }
                order[c] = j;
            }
        }

        for (int i = 0; i < n; i++) {
            if (seen[i]) {
                status[i] = 1;
            } else {
                if (status[i] == 1) status[i] = 2;
            }
        }
    }

    return true;
}

int main() {
    int tt;
    cin >> tt;

    while (tt--) {
        int n, m;
        cin >> n >> m;

        cout << (solve(n, m) ? "YES\n" : "NO\n");
    }

    return 0;
}
