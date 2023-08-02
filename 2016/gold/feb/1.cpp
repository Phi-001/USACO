#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
    if (fopen("cbarn.in", "r")) {
        freopen("cbarn.in", "r", stdin);
        freopen("cbarn.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++)
        cin >> c[i];

    for (int i = 0; i < n; i++)
        c[i]--;

    vector<int> psum(n);
    psum[0] = c[0];
    for (int i = 1; i < n; i++)
        psum[i] = psum[i - 1] + c[i];

    int idx;
    int min = 1e9;
    for (int i = 0; i < n; i++) {
        if (psum[i] < min) {
            min = psum[i];
            idx = (i + 1) % n;
        }
    }

    long long ans = 0;
    int pos = idx;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= c[(i + idx) % n]; j++) {
            long long d = (pos - (i + idx)) % n;
            ans += d * d;
            pos += 1;
        }
    }

    cout << ans;

    return 0;
}
