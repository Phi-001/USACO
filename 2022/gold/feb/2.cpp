#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int t, k;
    cin >> t >> k;
    t--;

    vector<long double> binom(t + 1);
    binom[0] = exp2((long double) -t);

    for (int i = 1; i <= t; i++) {
        binom[i] = binom[i - 1] * ((long double) (t - i + 1)) / ((long double) i);
    }

    vector<long double> prob(t + 1);
    prob[0] = binom[0];
    for (int i = 1; i <= t; i++)
        prob[i] = prob[i - 1] + binom[i];

    vector<long double> expect(t + 2);
    for (int i = t; i >= 0; i--)
        expect[i] = expect[i + 1] + binom[i] * (long double) i;

    long double ans = 0;

    struct Linear {
        long double a;
        long double b;
    };

    auto compose = [](Linear x, Linear y) {
        return Linear { x.a * y.a, x.a * y.b + x.b };
    };

    auto apply = [](Linear x, long double a) {
        return x.a * a + x.b;
    };

    int i = 0;
    while (i < k) {
        long double p = ans;
        vector<Linear> l;
        l.push_back({ prob[(int) p], expect[((int) p) + 1] });

        int j = k;
        while (j != 0) {
            l.push_back(compose(l.back(), l.back()));
            j >>= 1;
        }

        for (int j = l.size() - 1; j >= 0; j--) {
            if (apply(l[j], ans) < ceil(p) && (i + (1 << j)) < k) {
                ans = apply(l[j], ans);
                i += (1 << j);
            }
        }

        ans = apply(l[0], ans);
        i++;
    }

    cout << setprecision(10) << ans + 1.0 << "\n";

    return 0;
}
