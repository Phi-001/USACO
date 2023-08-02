#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

void visit(vector<map<int, int>> &v, vector<int> &c, int n, vector<pair<int, int>> &move, int k) {
    for (int i = 0; i < n; i++) {
        v[i][i]++;
        c[i] = i;
    }
    for (int i = 0; i < k; i++) {
        auto [ a, b ] = move[i];
        swap(c[a], c[b]);
        v[c[a]][a]++;
        v[c[b]][b]++;
    }
}

int main() {
    int n, k;
    long long m;
    cin >> n >> k >> m;

    vector<pair<int, int>> move(k);
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        move[i] = { a, b };
    }

    vector<map<int, int>> v(n);
    vector<int> c(n);
    visit(v, c, n, move, k);

    vector<int> inv(n);
    for (int i = 0; i < n; i++) inv[c[i]] = i;

    vector<map<int, int>> remainder(n);
    {
        vector<int> c(n);
        visit(remainder, c, n, move, m % k);
    }

    vector<bool> process(n);
    vector<int> ans(n);

    for (int j = 0; j < n; j++) {
        if (process[j]) continue;
        int i = j;
        vector<int> s;
        while (!process[i]) {
            process[i] = true;
            s.push_back(i);
            i = inv[i];
        }

        if (m / k >= s.size()) {
            map<int, int> total;
            for (int i = 0; i < s.size(); i++)
                for (auto [ k, v ] : v[s[i]])
                    total[k] += v;

            for (int i = 0; i < s.size(); i++) {
                for (auto [ k, v ] : remainder[s[(i + m / k) % s.size()]])
                    total[k] += v;
                ans[s[i]] = total.size();
                for (auto [ k, v ] : remainder[s[(i + m / k) % s.size()]]) {
                    total[k] -= v;
                    if (total[k] == 0) total.erase(k);
                }
            }
        } else {
            map<int, int> total;
            for (int i = 0; i < m / k; i++)
                for (auto [ k, v ] : v[s[i]])
                    total[k] += v;

            for (int i = 0; i < s.size(); i++) {
                if (i != 0) {
                    for (auto [ k, v ] : v[s[(i + m / k - 1) % s.size()]])
                        total[k] += v;
                    for (auto [ k, v ] : v[s[i - 1]]) {
                        total[k] -= v;
                        if (total[k] == 0) total.erase(k);
                    }
                }
                for (auto [ k, v ] : remainder[s[(i + m / k) % s.size()]])
                    total[k] += v;
                ans[s[i]] = total.size();
                for (auto [ k, v ] : remainder[s[(i + m / k) % s.size()]]) {
                    total[k] -= v;
                    if (total[k] == 0) total.erase(k);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) cout << ans[i] << "\n";

    return 0;
}
