#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

vector<int> parse_ints(std::string_view sv) {
    vector<int> result;
    int val = 0;
    bool in_number = false;

    for (char c : sv) {
        if (isdigit(c)) {
            val = val * 10 + (c - '0');
            in_number = true;
        } else {
            if (in_number) {
                result.push_back(val);
                val = 0;
                in_number = false;
            }
        }
    }
    if (in_number) result.push_back(val);

    return result;
}

bool test(int key, string& target, vector<vector<int>>& buttons) {
    string test = "";
    for (int i = 0; i < target.size(); i++) test += ".";
    for (int i = 0; i < buttons.size(); i++)
        if (key & (1 << i))
            for (int j : buttons[i]) test[j] = (test[j] == '.' ? '#' : '.');
    // std::cout << key << ' ' << test << std::endl;
    return test == target;
}

int main() {
    ifstream fp("in.txt");
    string line;

    vector<string> targets;
    vector<vector<vector<int>>> buttons;
    vector<vector<int>> joltages;

    while (getline(fp, line)) {
        if (line.empty()) continue;

        auto tokens =
            line | views::split(' ') |
            views::filter([](auto&& rng) { return !rng.empty(); }) |
            views::transform([](auto&& rng) {
                return string_view(&*rng.begin(), ranges::distance(rng));
            });

        bool first = true;
        buttons.emplace_back();

        for (auto tok : tokens) {
            if (first) {
                targets.push_back(string(tok));
                first = false;
                continue;
            }

            if (tok.starts_with('{')) {
                joltages.push_back(parse_ints(tok));
            } else {
                buttons.back().push_back(parse_ints(tok));
            }
        }
    }
    for (string& s : targets) s = s.substr(1, s.size() - 2);
    // finally done parsing
    // brute force
    ll ans = 0;
    for (int i = 0; i < targets.size(); i++) {
        int m = buttons[i].size();
        if (m > 10) std::cout << "BIG M AT " << i << ':' << m << std::endl;
        int cap = 1 << m;
        int best = 100;
        for (int key = 0; key < cap; key++) {
            if (test(key, targets[i], buttons[i]) && popcount((ull)key) < best)
                best = popcount((ull)key);
        }
        if (best == 100)
            std::cout << "NO SOL FOUND AT " << i << ":" << targets[i]
                      << std::endl;
        ans += best;
    }
    std::cout << ans << std::endl;
}
