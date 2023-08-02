#include <iostream>
#include <vector>

using namespace std;

int main() {
    if (fopen("balance.in", "r")) {
        freopen("balance.in", "r", stdin);
        freopen("balance.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    auto inv = [](vector<int> &a) {
        int count = 0;
        long long ans = 0;
        for (auto e : a) {
            if (e == 0) ans += count;
            else count++;
        }
        return ans;
    };

    auto zero = [](vector<int> &a) {
        vector<int> z;
        for (int i = 0; i < a.size(); i++)
            if (a[i] == 0) z.push_back(i);
        return z;
    };

    auto one = [](vector<int> &a) {
        vector<int> o;
        for (int i = 0; i < a.size(); i++)
            if (a[i] == 1) o.push_back(i);
        return o;
    };

    long long inva = inv(a);
    long long invb = inv(b);
    vector<int> za = zero(a);
    vector<int> zb = zero(b);
    vector<int> oa = one(a);
    vector<int> ob = one(b);

    auto self_left = [&](vector<int> &a, int i) { return i; };
    auto self_right = [&](vector<int> &a, int i) { return a.size() - i - 1; };
    auto other_left = [&](vector<int> &a, int i) { return a[i] - self_left(a, i); };
    auto other_right = [&](vector<int> &a, int i) { return (n - a[i] - 1) - self_right(a, i); };

    long long ans = abs(inva - invb);

    {
        long long ma = 0;
        long long mb = 0;
        long long ca = 0;
        long long cb = 0;
        for (int i = 0; i < ob.size(); i++) {
            int j = za.size() - 1 - i;
            if (j < 0) break;
            ma += (n - 1) - za[j] - i;
            mb += ob[i] - i;
            ca += other_left(za, j);
            cb += other_right(ob, i);
            ans = min(ans, abs((inva - ca) - (invb - cb)) + ma + mb + (long long) (i + 1) * (i + 1));
        }
    }

    {
        long long ma = 0;
        long long mb = 0;
        long long ca = 0;
        long long cb = 0;
        for (int i = 0; i < zb.size(); i++) {
            int j = oa.size() - 1 - i;
            if (j < 0) break;
            ma += (n - 1) - oa[j] - i;
            mb += zb[i] - i;
            ca += self_left(oa, j) - (n - oa[j] - 1);
            cb += self_right(zb, i) - (zb[i]);
            ans = min(ans, abs((inva + ca) - (invb + cb)) + ma + mb + (long long) (i + 1) * (i + 1));
        }
    }

    cout << ans << "\n";

    return 0;
}
