#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> freq(1e6 + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }

    vector<long long> count(1e6 + 2);
    for (int i = 1e6; i >= 0; i--) count[i] = count[i + 1] + freq[i];

    long long ans = 0;

    for (int i = 1; i <= 1e6; i++) {
        vector<int> piles;
        for (int j = i; j <= 1e6; j += i)
            piles.push_back(count[j] - count[min(j + i, (int) 1e6)]);

        vector<int> odd;
        for (int j = 0; j < piles.size(); j++)
            if (piles[j] % 2 == 1)
                odd.push_back(j);

        if (odd.size() == 1 && odd[0] == 0)
            ans += piles[odd[0]];

        if (odd.size() == 2 && odd[1] - odd[0] == 1)
            ans += piles[odd[1]];
    }

    cout << ans << "\n";

    return 0;
}
