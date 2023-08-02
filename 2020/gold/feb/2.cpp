#include <iostream>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;
struct Mint {
    int v;

    Mint () { v = 0; };
    Mint (int a) { v = (a + mod) % mod; }
    Mint& operator+=(const Mint& rhs) { this->v = (this->v + rhs.v) % mod; return *this; }
    Mint& operator*=(const Mint& rhs) { this->v = ((long long) this->v * rhs.v) % mod; return *this; }
    friend Mint operator*(Mint lhs, const Mint& rhs) { lhs *= rhs; return lhs; }
};

int main() {
    if (fopen("help.in", "r")) {
        freopen("help.in", "r", stdin);
        freopen("help.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> a(2 * n + 1);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[x]++;
        a[y]--;
    }

    vector<Mint> pow(n);
    pow[0] = 1;
    for (int i = 1; i < n; i++) pow[i] = pow[i - 1] * 2;

    int open = 0;
    Mint ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        open += a[i];
        if (a[i] == 1) ans += pow[n - open];
    }

    cout << ans.v;

    return 0;
}
