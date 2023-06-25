#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdio>
#include <array>
#include <map>

using namespace std;

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);

    int n;
    cin >> n;

    array<map<int, vector<int>>, 2> lines;
    vector<pair<int, int>> points;

    for (int i = 0; i < n + 2; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back({ x, y });
        lines[0][x].push_back(i);
        lines[1][y].push_back(i);
    }

    // 0 for vertical
    queue<pair<int, int>> visit;
    visit.push({ 0, 0 });
    visit.push({ 0, 1 });

    vector<int> dist(n + 2, -1);
    dist[0] = 0;

    while (!visit.empty()) {
        auto [ p, d ] = visit.front();
        visit.pop();

        int dir = !d;
        int coord = dir ? points[p].second : points[p].first;

        for (auto f : lines[dir][coord]) {
            if (dist[f] == -1) {
                dist[f] = dist[p] + 1;
                visit.push({ f, dir });
            }
        }
    }

    if (dist[1] == -1) cout << -1;
    else cout << dist[1] - 1;

    return 0;
}
