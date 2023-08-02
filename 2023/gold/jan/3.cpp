#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const long long mod = 1e9 + 7;

int inv(long long n) {
    // fermat's little theorem tells that
    // a^(p - 1) = 1 mod p
    // Then inverse of a is
    // a^(p - 2) a = 1 mod p
    int pow = mod - 2;
    long long inv = 1;
    long long sq = n;
    while (pow > 0) {
        if (pow & 1) {
            inv *= sq;
            inv %= mod;
        }
        pow >>= 1;
        sq *= sq;
        sq %= mod;
    }
    return inv;
}

int main() {
    const int max_fact = 1e6;
    vector<long long> fact(max_fact + 1);
    fact[0] = 1;
    for (int i = 1; i <= max_fact; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }

    int l;
    cin >> l;

    vector<int> a(l);
    for (int i = 0; i < l; i++) cin >> a[i];

    long long ans = 1;
    for (int i = 1; i < l; i++) {
        long long n = a[i - 1] / 2;
        long long k = a[i] / 2;
        long long binom;
        if (k < n) {
            binom = fact[n] * inv(fact[k]) % mod * inv(fact[n - k]) % mod;
        } else {
            k -= n;
            binom = fact[k + n - 1] * inv(fact[n - 1]) % mod * inv(fact[k]) % mod;
        }
        ans *= binom;
        ans %= mod;
    }

    cout << ans;

    return 0;
}
