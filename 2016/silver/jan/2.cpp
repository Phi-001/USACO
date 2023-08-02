#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

int main() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<int> prefix(n);

    int accum = 0;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        accum += a;
        accum %= 7;
        prefix[i] = accum;
    }

    int ans = 0;

    for (int i = 0; i < 7; i++) {
        int min = n + 1;
        int max = -1;
        for (int j = 0; j < n; j++) {
            if (prefix[j] == i) {
                min = std::min(j, min);
                max = std::max(j, max);
            }
        }
        ans = std::max(max - min, ans);
    }

    std::cout << ans;
}
