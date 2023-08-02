#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main() {
    vector<long long> pow3(40);
    pow3[0] = 1;
    for (int i = 1; i < 40; i++)
        pow3[i] = pow3[i - 1] * 3;

    int q;
    cin >> q;

    while (q--) {
        long long d, x, y;
        cin >> d >> x >> y;

        array<array<array<long long, 2>, 2>, 3> dp1, dp2;
        dp1 = {};
        dp1[1][0][0] = 1;

        for (int i = 0; i < 40; i++) {
            dp2 = {};
            int dd = d / pow3[i] % 3;
            int xd = x / pow3[i] % 3;
            int yd = y / pow3[i] % 3;

            for (int cmp = 0; cmp < 3; cmp++) {
                for (int xc = 0; xc < 2; xc++) {
                    for (int yc = 0; yc < 2; yc++) {
                        for (int j = 0; j < 3; j++) {
                            int nxd = (xd + xc + j) % 3;
                            int nxc = (xd + xc + j) / 3;
                            int nyd = (yd + yc + j) % 3;
                            int nyc = (yd + yc + j) / 3;
                            int ncmp = cmp;
                            if (j > dd) ncmp = 2;
                            if (j < dd) ncmp = 0;
                            if (nxd % 2 == nyd % 2)
                                dp2[ncmp][nxc][nyc] += dp1[cmp][xc][yc];
                        }
                    }
                }
            }
            swap(dp1, dp2);
        }
        cout << dp1[0][0][0] + dp1[1][0][0] << "\n";
    }

    return 0;
}
