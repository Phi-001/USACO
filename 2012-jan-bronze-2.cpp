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
    freopen("stacking.in", "r", stdin);
    freopen("stacking.out", "w", stdout);
    
    int n, k;
    std::cin >> n >> k;

    std::vector<int> modify(n);
    for (int i = 0; i < k; i++) {
        int a, b;
        std::cin >> a >> b;
        modify[a - 1] += 1;
        if (b < n) modify[b] -= 1;
    }

    std::vector<int> result(n);

    int current = 0;
    for (int i = 0; i < n; i++) {
        current += modify[i];
        result[i] = current;
    }

    std::sort(result.begin(), result.end());

    std::cout << result[n / 2] << std::endl;

    return 0;
}
