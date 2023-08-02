#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <utility>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <cstdio>

int main() {
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, m, r;
    std::cin >> n >> m >> r;

    std::vector<long long> cows(n);
    for (long long i = 0; i < n; i++) std::cin >> cows[i];

    std::vector<std::pair<long long, long long>> buy(m);
    for (long long i = 0; i < m; i++) {
        long long p, q;
        std::cin >> q >> p;
        buy[i] = { p, q };
    }

    std::vector<long long> rental(r);
    for (long long i = 0; i < r; i++) std::cin >> rental[i];

    std::sort(cows.begin(), cows.end());
    std::sort(buy.begin(), buy.end());
    std::sort(rental.begin(), rental.end(), std::greater<long long>());

    std::vector<long long> rent_psum(n + 1);
    rent_psum[0] = 0;
    for (long long i = 1; i <= n; i++) {
        rent_psum[i] = rent_psum[i - 1];
        if (i - 1 < r) {
            rent_psum[i] += rental[i - 1];
        }
    }

    std::vector<long long> sell_psum(n + 1);
    sell_psum[n] = 0;
    for (long long i = n - 1; i >= 0; i--) {
        sell_psum[i] = sell_psum[i + 1];

        long long milk = cows[i];
        while (milk > 0) {
            if (buy.size() == 0) break;
            auto [ p, q ] = buy[buy.size() - 1];
            long long sell = std::min(milk, q);
            sell_psum[i] += sell * p;
            milk -= sell;
            if (sell == q) buy.pop_back();
            else buy[buy.size() - 1] = { p, q - sell };
        }
    }

    long long ans = 0;

    for (long long i = 0; i < n + 1; i++) {
        long long profit = rent_psum[i] + sell_psum[i];
        ans = std::max(ans, profit);
    }

    std::cout << ans;

    return 0;
}
