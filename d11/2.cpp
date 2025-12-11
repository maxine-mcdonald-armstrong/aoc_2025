#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

struct Val {
    ll neither;
    ll fft;
    ll dac;
    ll both;
    Val &operator+=(const Val &other) {
        neither += other.neither;
        fft += other.fft;
        dac += other.dac;
        both += other.both;
        return *this;
    }
    ll sum() { return neither + fft + dac + both; }
};

void solve(unordered_map<string, vector<string>> &tree,
           unordered_map<string, vector<string>> &rev_tree,
           unordered_set<string> &reachable, unordered_map<string, Val> &ans,
           string cur) {
    Val c = {0, 0, 0, 0};
    for (string &target : rev_tree[cur]) {
        if (!reachable.contains(target)) continue;
        if (ans[target].sum() == 0)
            solve(tree, rev_tree, reachable, ans, target);
        c += ans[target];
    }
    if (cur == "fft") {
        c.both += c.dac;
        c.dac = 0;
        c.fft += c.neither;
        c.neither = 0;
    }
    if (cur == "dac") {
        c.both += c.fft;
        c.fft = 0;
        c.dac += c.neither;
        c.neither = 0;
    }
    ans[cur] = c;
    std::cout << "D " << cur << ' ' << ans[cur].neither << ' ' << ans[cur].fft
              << ' ' << ans[cur].dac << ' ' << ans[cur].both << '\n';
}

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample2.txt", std::ios_base::in);
    unordered_map<string, vector<string>> map;
    unordered_map<string, vector<string>> rev_map;
    string line;
    while (getline(fp, line)) {
        if (line.empty()) continue;

        string key;
        vector<string> vals;

        int pos = line.find(':');
        key = line.substr(0, pos);

        string rest = line.substr(pos + 1);
        stringstream ss(rest);

        string w;
        while (ss >> w) {
            vals.push_back(w);
            rev_map[w].push_back(key);
        }

        map[key] = vals;
    }
    unordered_set<string> reachable;
    vector<string> to_visit = {"svr"};
    reachable.insert("svr");
    while (!to_visit.empty()) {
        string next = to_visit.back();
        to_visit.pop_back();
        for (string &neighbour : map[next]) {
            if (!reachable.contains(neighbour)) {
                reachable.insert(neighbour);
                to_visit.push_back(neighbour);
            }
        }
    }
    unordered_map<string, Val> ans;
    ans["svr"] = {1, 0, 0, 0};
    solve(map, rev_map, reachable, ans, "out");
    std::cout << ans["out"].both;
}
