#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("in.txt", std::ios_base::in);
    int cur = 50;
    int ans = 0;
    char c;
    int x;
    while (fp >> c >> x) {
        if (c == 'L')
            cur -= x;
        else
            cur += x;
        cur = (cur % 100 + 100) % 100;
        if (cur == 0) ans++;
    }
    std::cout << ans << std::endl;
}
