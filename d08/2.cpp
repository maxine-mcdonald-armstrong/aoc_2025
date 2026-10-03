#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using namespace std;

double dist(std::vector<std::tuple<ll, ll, ll>> &A, int a, int b) {
    double u, v, w;
    u = std::abs(std::get<0>(A[a]) - std::get<0>(A[b]));
    u *= u;
    v = std::abs(std::get<1>(A[a]) - std::get<1>(A[b]));
    v *= v;
    w = std::abs(std::get<2>(A[a]) - std::get<2>(A[b]));
    w *= w;
    return std::sqrt(u + w + v);
}

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample.txt", std::ios_base::in);
    ll x, y, z;
    char _c;
    std::vector<std::tuple<ll, ll, ll>> A;
    while (fp >> x >> _c >> y >> _c >> z) {
        A.push_back({x, y, z});
    }
    atcoder::dsu d(A.size());
    int connected_components = A.size();
    std::vector<std::set<int>> graph(A.size());
    std::pair<int, int> best = {0, 0};
    while (connected_components > 1) {
        double best_d = 1e100;
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                if (i == j) continue;
                if (graph[i].contains(j)) continue;
                if (dist(A, i, j) < best_d) {
                    best = {i, j};
                    best_d = dist(A, i, j);
                }
            }
        }

        std::cout << "D " << best_d << ' ' << best.first << ' ' << best.second
                  << ' ' << connected_components << std::endl;
        if (!d.same(best.first, best.second)) connected_components--;
        d.merge(best.first, best.second);
        graph[best.first].insert(best.second);
        graph[best.second].insert(best.first);
    }
    // loop ended cuz we connected all.
    ll ans = std::get<0>(A[best.first]) * std::get<0>(A[best.second]);
    std::cout << ans << std::endl;
}
