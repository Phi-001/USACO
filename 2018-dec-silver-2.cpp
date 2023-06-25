#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

struct Cow {
    int seniority;
    long long a;
    int t;

    bool operator<(const Cow &other) const {
        return seniority > other.seniority;
    }
};

bool comp_time(const Cow &a, const Cow &b) {
    return a.a < b.a;
}

int main() {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        long long a;
        int t;
        cin >> a >> t;
        cows[i] = { i, a, t };
    }

    sort(cows.begin(), cows.end(), comp_time);

    Cow current;
    bool eating = false;
    long long start;
    priority_queue<Cow> waiting;
    long long time = -1;
    long long ans = -1;

    int i = 0;
    while (i < n || !waiting.empty()) {
        if (eating) {
            if (i >= n || start + current.t < cows[i].a) {
                eating = false;
                time = start + current.t;
            } else {
                time = cows[i].a;
                while (i < n && cows[i].a == time) {
                    waiting.push(cows[i]);
                    i++;
                }
            }
        } else {
            if (!waiting.empty()) {
                eating = true;
                current = waiting.top();
                start = time;
                waiting.pop();
                ans = max(ans, start - current.a);
                // cout << "cow " << (current.seniority + 1) << " is eating" << endl;
            } else {
                time = cows[i].a;
                while (i < n && cows[i].a == time) {
                    waiting.push(cows[i]);
                    i++;
                }
            }
        }

        // cout << time << endl;
    }

    cout << ans;

    return 0;
}
