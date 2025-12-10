#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

int main() {
    // std::fstream fp("in.txt", std::ios_base::in);
    std::fstream fp("in.txt", std::ios_base::in);
    string s;
    vector<string> grid;
    while (fp >> s) grid.push_back(s);
    map<int, ll> is;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < m; i++)
        if (grid[0][i] == 'S') is[i] = 1;
    for (int i = 1; i < n; i++) {
        map<int, ll> new_is;
        for (auto& [old_i, count] : is) {
            if (grid[i][old_i] == '^') {
                new_is[old_i - 1] += count;
                new_is[old_i + 1] += count;
            } else
                new_is[old_i] += count;
        }
        is = new_is;
    }
    ll ans = 0;
    for (auto& [a, c] : is) ans += c;
    std::cout << ans << endl;
}
