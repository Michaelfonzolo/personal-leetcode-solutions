// UGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) {
            return res;
        } else if (digits.size() == 1) {
            return getLetters(digits[0]);
        }
        vector<string> first_chars = getLetters(digits[0]);
        vector<string> next_res = letterCombinations(digits.substr(1, digits.size() - 1));
        for (string c : first_chars) {
            for (string last : next_res) {
                res.push_back(c + last);
            }
        }
        return res;
    }
    
    vector<string> getLetters(char digit) {
        vector<string> res;
        if (digit == '7') {
            res = {"p", "q", "r", "s"};
        } else if (digit == '8') {
            res = {"t", "u", "v"};   
        } else if (digit == '9') {
            res = {"w", "x", "y", "z"};
        } else {
            for (int i = 0; i < 3; i++) {
                res.push_back(string(1, 97 + i + 3 * (digit - '2')));
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<string> res = s.letterCombinations("23");
    for (string str : res) {
        cout << str << endl;
    }

    return 0;
}