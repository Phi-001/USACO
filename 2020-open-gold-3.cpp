#include <iostream>
#include <vector>

using namespace std;

int main() {
    if (fopen("exercise.in", "r")) {
        freopen("exercise.in", "r", stdin);
        freopen("exercise.out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<int> primes(n + 1, 1);
    vector<long long> dp(n + 1);
    dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        if (!primes[i]) continue;
        for (int j = 2 * i; j <= n; j += i)
            primes[j] = 0;

        for (int j = n; j >= 0; j--) {
            int pow = i;
            while (pow <= j) {
                dp[j] = (dp[j] + (dp[j - pow] * pow) % m) % m;
                pow *= i;
            }
        }
    }

    long long ans = 0;

    for (int i = 0; i <= n; i++) {
        ans = (ans + dp[i]) % m;
    }

    cout << ans;

    return 0;
}
