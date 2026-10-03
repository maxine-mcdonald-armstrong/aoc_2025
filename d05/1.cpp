#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("in.txt", std::ios_base::in);
    int q;
    fp >> q;
    std::vector<std::pair<ll, ll>> ranges(q);
    for (int i = 0; i < q; i++) {
        ll a, b;
        char _c;
        fp >> a >> _c >> b;
        ranges.push_back({a, b});
    }
    int n;
    fp >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        fp >> a;
        for (auto &[l, r] : ranges) {
            if (l <= a && r >= a) {
                ans++;
                break;
            }
        }
    }
    std::cout << ans << std::endl;
}
