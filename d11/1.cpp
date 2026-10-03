#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

void solve(unordered_map<string, vector<string>> &tree,
           unordered_map<string, vector<string>> &rev_tree,
           unordered_set<string> &reachable, unordered_map<string, ll> &ans,
           string cur) {
    ll c = 0;
    for (string &target : rev_tree[cur]) {
        if (!reachable.contains(target)) continue;
        if (ans[target] == 0) solve(tree, rev_tree, reachable, ans, target);
        c += ans[target];
    }
    ans[cur] = c;
    std::cout << "D " << cur << ' ' << ans[cur] << '\n';
}

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample.txt", std::ios_base::in);
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
    vector<string> to_visit = {"you"};
    reachable.insert("you");
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
    unordered_map<string, ll> ans;
    ans["you"] = 1;
    solve(map, rev_map, reachable, ans, "out");
    std::cout << ans["out"];
}
