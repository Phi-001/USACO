#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long ans = 1;

    for (int i = 0; i < n; i++) {
        ans *= upper_bound(a.begin(), a.end(), b[i]) - a.begin() - i;
    }

    cout << ans;

    return 0;
}
