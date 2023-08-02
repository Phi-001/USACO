#include <iostream>
#include <vector>
#include <cstdio>
#include <set>

using namespace std;

int main() {
    //if (fopen("262144.in", "r")) {
    //    freopen("262144.in", "r", stdin);
    //    freopen("262144.out", "w", stdout);
    //}

    int n;
    cin >> n;

    vector<int> diff(n + 1);
    vector<int> idx(n + 1, -1);
    set<int> s;

    s.insert(0);
    s.insert(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto it = s.lower_bound(x);
        int r = *it;
        int l = *(--it);

        if (idx[r] > idx[l]) {
            diff[x] += 1;
            diff[r] -= 1;
        }

        s.insert(x);
        idx[x] = i;
    }

    int psum = 0;
    for (int i = 0; i <= n; i++) {
        psum += diff[i];
        cout << psum << "\n";
    }

    return 0;
}
