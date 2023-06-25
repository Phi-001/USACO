#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <utility>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <cstdio>

std::vector<long long> pos;
std::vector<long long> neg;
std::vector<long long> id;

bool cmp(int a, int b) {
    if (neg[a] == neg[b]) return pos[a] > pos[b];
    return neg[a] < neg[b];
}

int main() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        long long x, y;
        std::cin >> x >> y;
        pos.push_back(x + y);
        neg.push_back(x - y);
        id.push_back(i);
    }

    std::sort(id.begin(), id.end(), cmp);

    long long end = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (pos[id[i]] > end) {
            end = pos[id[i]];
            ans++;
        }
    }

    std::cout << ans;

    return 0;
}
