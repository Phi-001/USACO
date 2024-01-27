#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    vector<long long> left(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) left[i] = 0;
        else left[i] = left[i - 1] + (a[i] - a[i - 1]) * i;
    }

    vector<long long> right(n);
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) right[i] = 0;
        else right[i] = right[i + 1] + (a[i + 1] - a[i]) * (n - i - 1);
    }

    int q;
    cin >> q;
    for (int j = 0; j < q; j++) {
        long long a, b;
        cin >> a >> b;

        int i = b * (n - 1) / (a + b);

        if (b == n - 1) cout << a * left[i] + b * right[i];
        else cout << min(a * left[i] + b * right[i], a * left[i + 1] + b * right[i + 1]);
        cout << "\n";
    }

    return 0;
}
