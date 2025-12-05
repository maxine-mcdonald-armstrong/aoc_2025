#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("sample.txt", std::ios_base::in);
    int q;
    fp >> q;
    std::vector<std::pair<ll, ll>> ranges;
    for (int i = 0; i < q; i++) {
        ll a, b;
        char _c;
        fp >> a >> _c >> b;
        ranges.push_back({a, b});
    }
    std::sort(ranges.begin(), ranges.end());
    ll ans = 0;
    ll prev_r = -1;
    for (auto range : ranges) {
        ll l = range.first;
        ll r = range.second;
        std::cout << "D " << prev_r << ' ' << l << ' ' << r << std::endl;
        if (r <= prev_r) continue;
        if (l <= prev_r) l = prev_r + 1;
        std::cout << "DD " << "x " << l << ' ' << r << ' ' << r - l + 1 << std::endl;
        ans += r - l + 1;
        prev_r = r;
        if (ans < 0) {
            std::cout << "OVERFLOW DETECTED " << ans;
            return 1;
        }
    }
    std::cout << ans << std::endl;
}
