#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int c;
    string s;
    vector<int> childs;
    long long size;
    int n;

    Node (char c, string s) : c(c - 'a'), s(s), childs(), size(0), n(s.size()) {}

    void output(long long i, long long l, long long r, vector<Node> &nodes) {
        if (i + size < l || i > r) return;

        for (int j = 0; j < n && i <= r; j++) {
            int k = childs[j];
            if (k != -1) {
                nodes[k].output(i, l, r, nodes);
                i += nodes[k].size;
            } else {
                if (l <= i && i <= r) cout << s[j];
                i++;
            }
        }
    }
};

int main() {
    long long l, r;
    int q;
    cin >> l >> r >> q;

    l--; r--;

    vector<Node> nodes;

    for (int i = 0; i < q; i++) {
        char c;
        string s;
        cin >> c >> s;
        nodes.push_back(Node(c, s));
    }

    vector<int> current(26, -1);

    for (int i = q - 1; i >= 0; i--) {
        if (nodes[i].n == 1) {
            current[nodes[i].c] = current[nodes[i].s[0] - 'a'];
            if (current[nodes[i].c] != -1) continue;
        }

        for (auto c : nodes[i].s) {
            c -= 'a';
            if (current[c] != -1)
                nodes[i].size += nodes[current[c]].size;
            else
                nodes[i].size += 1;
            if (nodes[i].size >= 1e18) nodes[i].size = 1e18;
            nodes[i].childs.push_back(current[c]);
        }
        current[nodes[i].c] = i;
    }

    if (current[0] == -1) cout << 0;
    else nodes[current[0]].output(0, l, r, nodes);

    return 0;
}
