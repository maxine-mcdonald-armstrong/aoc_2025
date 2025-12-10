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
    set<int> is;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < m; i++)
        if (grid[0][i] == 'S') is.insert(i);
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        set<int> new_is;
        for (int old_i : is) {
            if (grid[i][old_i] == '^') {
                new_is.insert(old_i - 1);
                new_is.insert(old_i + 1);
                ans++;
            } else
                new_is.insert(old_i);
        }
        is = new_is;
    }
    std::cout << ans << endl;
}
