#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    std::string s;
    std::vector<std::string> grid;
    while (fp >> s) {
        grid.push_back(s);
    }
    ll ans = 0;
    int n = grid.size();
    int m = grid[0].size();
    ll prev = 1;
    while (prev > 0) {
        ll next = 0;
        std::vector<std::string> nextgrid = grid;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != '@') continue;
                int count = 0;
                for (int k = j - 1; k <= j + 1; k++) {
                    if (k < 0 || k >= m) continue;
                    for (int l = i - 1; l <= i + 1; l++) {
                        if (l < 0 || l >= n) continue;
                        if (l == i && k == j) continue;
                        if (grid[l][k] == '@') count++;
                    }
                }
                if (count < 4) {
                    nextgrid[i][j] = '.';
                    next++;
                }
            }
        }
        ans += next;
        prev = next;
        grid = nextgrid;
    }
    std::cout << ans << std::endl;
}
