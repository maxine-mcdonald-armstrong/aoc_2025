#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("in.txt", std::ios_base::in);
    std::string s;
    ll ans;
    while (fp >> s) {
        int ai = 0;
        for (int i = 1; i < s.size() - 1; i++)
            if (s[i] > s[ai]) ai = i;
        int bi = ai + 1;
        for (int i = bi; i < s.size(); i++)
            if (s[i] > s[bi]) bi = i;
        ans += (s[ai] - '0') * 10 + (s[bi] - '0');
    }
    std::cout << ans << std::endl;
}
