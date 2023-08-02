#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;

typedef array<int, 2> Point;
typedef array<int, 3> Tri;

Point p[40];

int cross(Point a, Point b, Point c) {
    array<int, 2> x = { b[0] - a[0], b[1] - a[1] };
    array<int, 2> y = { c[0] - a[0], c[1] - a[1] };
    return x[0] * y[1] - y[0] * x[1];
}

int area(Tri t) {
    return abs(cross(p[t[0]], p[t[1]], p[t[2]]));
}

bool inside(Tri t, int p) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        swap(t[i], p);
        sum += area(t);
        swap(t[i], p);
    }
    sum -= area(t);
    return sum == 0;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) cin >> p[i][0] >> p[i][1];

    vector<Tri> triangles;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                triangles.push_back({ i, j, k });

    sort(triangles.begin(), triangles.end(), [](Tri a, Tri b) {
        return area(a) < area(b);
    });

    long long ans = 0;

    vector<vector<vector<vector<long long>>>> dp(n, vector<vector<vector<long long>>>(n, vector<vector<long long>>(n, vector<long long>(n))));

    for (auto &t : triangles) {
        int in = 0;
        vector<Tri> nex;
        for (int i = 0; i < n; i++) {
            if (inside(t, i)) {
                in++;
            } else {
                for (int j = 0; j < 3; j++) {
                    Tri test = t;
                    test[j] = i;
                    sort(test.begin(), test.end());
                    if (inside(test, t[j])) nex.push_back(test);
                }
            }
        }

        in -= 3;

        dp[t[0]][t[1]][t[2]][0] = 1;

        for (int i = 0; i <= in; i++) {
            long long v = dp[t[0]][t[1]][t[2]][i];
            if (i < in)
                dp[t[0]][t[1]][t[2]][i + 1] = (dp[t[0]][t[1]][t[2]][i + 1] + (in - i) * v % mod) % mod;
            for (auto u : nex)
                dp[u[0]][u[1]][u[2]][i + 1] = (dp[u[0]][u[1]][u[2]][i + 1] + v) % mod;
        }
        if (in == n - 3)
            ans = (ans + dp[t[0]][t[1]][t[2]][in]) % mod;
    }

    cout << (6 * ans) % mod << "\n";

    return 0;
}
