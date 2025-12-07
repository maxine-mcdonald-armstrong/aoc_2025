#include <bits/stdc++.h>

#include <atcoder/all>

using ll = long long;
using ull = unsigned long long;

using namespace std;

int main() {
    std::fstream fp("in.txt", std::ios_base::in);
    // std::fstream fp("sample.txt", std::ios_base::in);
    string s;
    vector<string> input;
    while (getline(fp, s)) {
        input.push_back(s);
        cout << s << endl;
    }
    string commands = input[input.size() - 1];
    input.pop_back();
    char op = commands[0];
    vector<int> nums;
    ll ans = 0;
    for (int i = 0; i < input[0].size(); i++) {
        bool end = true;
        for (string &line : input)
            if (line[i] != ' ') end = false;
        cout << end << ' ';
        if (end) {
            if (op == '+') {
                int cur = 0;
                for (int x : nums) cur += x;
                ans += cur;
            } else {
                ll cur = 1;
                for (int x : nums) cur *= x;
                ans += cur;
            }
            op = commands[i + 1];
            nums = vector<int>();
            cout << endl;
        } else {
            int num = 0;
            int c = 1;
            for (auto pt = input.rbegin(); pt != input.rend(); pt++) {
                if ((*pt)[i] == ' ') continue;
                num += c * ((*pt)[i] - '0');
                c *= 10;
            }
            nums.push_back(num);
            cout << num << ' ';
        }
    }
    if (op == '+') {
        int cur = 0;
        for (int x : nums) cur += x;
        ans += cur;
    } else {
        ll cur = 1;
        for (int x : nums) cur *= x;
        ans += cur;
    }
    cout << ans << endl;
}
