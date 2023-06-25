#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

const long long M = 1e9 + 9;
const long long B = 9973;

vector<long long> ps = { 1 };

struct HashedString {
    vector<long long> p;

    HashedString (vector<int> s) {
        while (ps.size() < s.size())
            ps.push_back(ps.back() * B % M);

        p.resize(s.size());

        p[0] = 0;

        for (int i = 0; i < s.size(); i++)
            p[i + 1] = (p[i] * B + s[i]) % M;
    }

    int hash(int a, int b) {
        return (p[b + 1] - p[a] * ps[b + 1 - a] % M + M) % M;
    }
};

int main() {
    if (fopen("lightsout.in", "r")) {
        freopen("lightsout.in", "r", stdin);
        freopen("lightsout.out", "w", stdout);
    }

    int n;
    cin >> n;

    vector<int> xs(n);
    vector<int> ys(n);

    for (int i = 0; i < n; i++)
        cin >> xs[i] >> ys[i];

    vector<int> s;

    int total = 0;

    for (int i = 0; i < n; i++) {
        int dir0 = xs[i] == xs[(i + 1) % n];
        int dir1 = xs[i] != xs[(i - 1 + n) % n] ? xs[i] < xs[(i - 1 + n) % n] : ys[i] < ys[(i - 1 + n) % n];
        int dir2 = xs[i] != xs[(i + 1) % n] ? xs[i] < xs[(i + 1) % n] : ys[i] < ys[(i + 1) % n];
        dir0 = 2 * dir0 - 1;
        dir1 = 2 * dir1 - 1;
        dir2 = 2 * dir2 - 1;
        s.push_back(dir0 * dir1 * dir2);

        int l = abs(xs[i] - xs[(i + 1) % n]) + abs(ys[i] - ys[(i + 1) % n]);
        total += l;
        s.push_back(l);
    }

    vector<int> shortest(n);
    vector<int> clockwise(n);

    int d = 0;
    for (int i = 0; i < n; i++) {
        shortest[i] = min(d, total - d);
        clockwise[i] = total - d;
        d += abs(xs[i] - xs[(i + 1) % n]) + abs(ys[i] - ys[(i + 1) % n]);
    }

    HashedString hashed(s);

    bool works = false;
    vector<int> dist(n, -1);
    int steps = 0;
    map<int, int> hashes;

    dist[0] = 0;

    while (!works) {
        for (int i = 0; i < n; i++) {
            if (dist[i] != -1) continue;
            if (i + steps >= n) {
                dist[i] = clockwise[i];
                continue;
            }

            int h = hashed.hash(2 * i, 2 * (i + steps));
            if (hashes.count(h)) {
                dist[hashes[h]] = -1;
            } else {
                dist[i] = shortest[i + steps] + clockwise[i] - clockwise[i + steps];
                hashes[h] = i;
            }
        }

        works = true;
        for (int i = 0; i < n; i++)
            works = works && (dist[i] != -1);

        steps++;
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
        ans = max(ans, dist[i] - shortest[i]);

    cout << ans;

    return 0;
}
