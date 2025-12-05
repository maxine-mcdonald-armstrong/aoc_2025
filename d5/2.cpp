#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::fstream fp("in.txt", std::ios_base::in);
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
    std::vector<std::pair<ll, ll>> merged_ranges;
    std::pair<ll, ll> prev_range = ranges[0];
    for (int i = 1; i < q; i++) {
        ll l = ranges[i].first;
        ll r = ranges[i].second;
        if (r <= prev_range.second) continue;
        if (l <= prev_range.second) {
            prev_range = {prev_range.first, r};
            continue;
        }
        merged_ranges.push_back(prev_range);
        prev_range = {l, r};
    }
    merged_ranges.push_back(prev_range);
    for (auto &[l, r] : merged_ranges) {
        ans += r - l + 1;
    }
    std::cout << ans << std::endl;
}
