#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using POINT = std::pair<ll, ll>;
using LINE = std::pair<POINT, POINT>;

using namespace std;

bool p_in_poly(POINT p, std::set<POINT> &edge_points, std::set<LINE> &edges) {
    if (edge_points.contains(p)) return true;
    int i = 0;
    for (auto &[u, v] : edges) {
        if (u.second == v.second) continue;
        bool u_above = u.second > p.second;
        bool v_above = v.second > p.second;
        if (u_above != v_above) {
            if (u.first > p.first) {
                i++;
            }
        }
    }
    return i % 2 == 1;
}

bool e_in_poly(LINE &e, std::set<POINT> &edge_points, std::set<LINE> &edges) {
    auto &[a, b] = e.first;
    auto &[c, d] = e.second;
    if (a == c) {
        for (ll ny = std::min(b, d); ny <= std::max(b, d); ny++)
            if (!p_in_poly({a, ny}, edge_points, edges)) return false;
    } else {
        for (ll nx = std::min(a, c); nx <= std::max(a, c); nx++)
            if (!p_in_poly({nx, b}, edge_points, edges)) return false;
    }
    return true;
}

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample.txt", std::ios_base::in);
    ll x, y;
    char _c;
    std::set<LINE> edges;
    std::set<POINT> points;
    std::set<POINT> edge_points;
    auto it = points.end();
    POINT first = {0, 0};
    while (fp >> x >> _c >> y) {
        points.insert({x, y});
        if (it != points.end()) {
            edges.insert({*it, {x, y}});
            if (it->first == x)
                for (int ny = std::min(y, it->second);
                     ny <= std::max(y, it->second); ny++)
                    edge_points.insert({x, ny});
            else
                for (int nx = std::min(x, it->first);
                     nx <= std::max(x, it->first); nx++)
                    edge_points.insert({nx, y});
        } else
            first = {x, y};
        it = points.find({x, y});
    }
    if (it->first == first.first)
        for (int ny = std::min(it->second, first.second);
             ny <= std::max(it->second, first.second); ny++)
            edge_points.insert({first.first, ny});
    else
        for (int nx = std::min(it->first, first.first);
             nx <= std::max(it->first, first.first); nx++)
            edge_points.insert({nx, first.second});
    edges.insert({*it, first});
    ll best = 0;
    for (auto &[a, b] : points) {
        std::cout << best << std::endl;
        for (auto &[c, d] : points) {
            POINT u = {a, d};
            POINT v = {c, b};
            LINE w = {{a, b}, u};
            LINE x = {{a, b}, v};
            LINE y = {{c, d}, u};
            LINE z = {{c, d}, v};
            bool fits = true;
            fits = fits && p_in_poly(u, edge_points, edges);
            fits = fits && p_in_poly(v, edge_points, edges);
            fits = fits && e_in_poly(w, edge_points, edges);
            fits = fits && e_in_poly(x, edge_points, edges);
            fits = fits && e_in_poly(y, edge_points, edges);
            fits = fits && e_in_poly(z, edge_points, edges);
            if (fits)
                best = std::max(best,
                                (std::abs(d - b) + 1) * (std::abs(c - a) + 1));
        }
    }
    std::cout << best;
}
