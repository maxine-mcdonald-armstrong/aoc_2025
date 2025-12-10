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
    std::vector<std::set<int>> graph(A.size());
    for (int t = 0; t < 1000; t++) {
        std::pair<int, int> best = {0, 0};
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
                  << std::endl;
        graph[best.first].insert(best.second);
        graph[best.second].insert(best.first);
    }
    std::multiset<ll> sizes;
    std::vector<bool> visited(A.size(), false);
    visited[0] = true;
    int k = 0;
    int s = 0;
    std::vector<int> to_visit = {0};
    while (k < A.size()) {
        if (to_visit.empty()) {
            std::cout << "D " << k << ' ' << s << std::endl;
            sizes.insert(s);
            s = 0;
            while (++k < A.size())
                if (!visited[k]) {
                    to_visit.push_back(k);
                    visited[k] = true;
                    break;
                }
        }
        if (k >= A.size()) break;
        int cur = to_visit.back();
        to_visit.pop_back();
        s++;
        for (int neighbour : graph[cur]) {
            if (!visited[neighbour]) to_visit.push_back(neighbour);
            visited[neighbour] = true;
        }
    }
    if (s > 0) sizes.insert(s);
    ll ans = 1;
    auto it = sizes.rbegin();
    for (int i = 0; i < 3; i++) {
        std::cout << "D " << *it << std::endl;
        ans *= *(it++);
    }
    std::cout << ans << std::endl;
}
