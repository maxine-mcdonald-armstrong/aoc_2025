#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("in.txt", std::ios_base::in);
    std::string s;
    ll ans = 0;
    while (fp >> s) {
        ll m = 100000000000;
        int ai = -1;
        for (int k = s.size() - 11; k <= s.size(); k++) {
            int bi = ai + 1;
            for (int i = bi; i < k; i++)
                if (s[i] > s[bi]) bi = i;
            ans += m * (s[bi] - '0');
            ai = bi;
            m /= 10;
        }
    }
    std::cout << ans << std::endl;
}
