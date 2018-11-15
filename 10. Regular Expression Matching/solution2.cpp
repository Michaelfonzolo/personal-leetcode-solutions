// This is the better DP solution to this problem. It's not mine, but I thought I'd implement it to learn how DP works.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch_recursive(string s, string p) {
        cout << s << " " << p << endl;
        if (p.empty()) 
            return s.empty();

        int pn = p.size(), sn = s.size();
        bool first_char_match = (sn > 0) && (p[0] == '.' || p[0] == s[0]);

        if (pn > 1 && p[1] == '*') {
            return isMatch_recursive(s, p.substr(2, pn - 2)) ||
                   (first_char_match && isMatch_recursive(s.substr(1, sn - 1), p));
        }
        return first_char_match && 
               isMatch_recursive(s.substr(1, sn - 1), p.substr(1, pn - 1));
    }

    bool isMatch_dynamic(string s, string p) {
        if (p.empty())
            return s.empty();

        int pn = p.size(), sn = s.size();
        // memo[si][pi] == isMatch_recursive(s[si:], p[pi:]);
        vector<vector<int>> memo(sn + 1, vector<int>(pn + 1, -1));
        return _isMatch_dynamic(s, p, 0, 0, &memo);
    }

    bool _isMatch_dynamic(string s, string p, int si, int pi, vector<vector<int>> *memo) {
        int pn = p.size(), sn = s.size();
        if ((*memo)[si][pi] > -1) {
            return (*memo)[si][pi];
        }

        int result = 0;
        if (pi == pn) {
            result = (int)(si == sn);
        }
        else {
            bool first_char_match = (si < sn) && (p[pi] == '.' || p[pi] == s[si]);
            if (pi + 1 < pn && p[pi + 1] == '*') {
                result = (int)(_isMatch_dynamic(s, p, si, pi + 2, memo) ||
                               (first_char_match && _isMatch_dynamic(s, p, si + 1, pi, memo)));
            }
            else {
                result = (int)(first_char_match && 
                               _isMatch_dynamic(s, p, si + 1, pi + 1, memo));
            }
        }
        (*memo)[si][pi] = result;
        return result;
    }
};

int main(int argc, char const *arvg[]) {
    Solution s;

    /*
    cout << s.isMatch_recursive("", ".*") << endl;
    cout << s.isMatch_recursive("", "c*d*") << endl;
    cout << s.isMatch_recursive("", "..*") << endl;
    */

    stringstream ss;
    string input, input_string, input_pattern;
    while (getline(cin, input) && !input.empty()) {
        ss = stringstream(input);
        ss >> input_string;
        ss >> input_pattern;
        cout << s.isMatch_dynamic(input_string, input_pattern) << endl;
    }
    
    return 0;
}