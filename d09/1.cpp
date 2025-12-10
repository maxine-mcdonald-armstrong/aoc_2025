#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample.txt", std::ios_base::in);
    ll x, y;
    char _c;
    std::set<std::pair<ll, ll>> points;
    while (fp >> x >> _c >> y) {
        points.insert({x, y});
    }
    ll best = 0;
    for (auto &[a, b] : points) {
        for (auto &[c, d] : points) {
            std::pair<ll, ll> u = {a, d};
            std::pair<ll, ll> v = {c, b};
            if (!points.contains(u) && !points.contains(v))
                best = std::max(best,
                                (std::abs(d - b) + 1) * (std::abs(c - a) + 1));
        }
    }
    std::cout << best;
}
