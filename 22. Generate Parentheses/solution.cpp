/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0) {
            return {};
        }
        return generateParenthesis_recursive(n);
    }

    vector<vector<string>*> memo;
    vector<string> generateParenthesis_recursive(unsigned int n) {
        if (n < memo.size()) {
            return *(memo[n]);
        }

        vector<string> result;
        if (n == 0) {
            result = {""};
        }
        else if (n == 1) {
            result = {"()"};
        } 
        else if (n > 1) {
            vector<string> left, right;
            for (unsigned int k = 0; k < n; k++) {
                left  = generateParenthesis_recursive(k);
                right = generateParenthesis_recursive(n - k - 1);
                for (auto left_parenths : left) {
                    for (auto right_parenths : right) {
                        result.push_back("(" + left_parenths + ")" + right_parenths);
                    }
                }
            }
        }
        
        while (memo.size() <= n) {
            memo.push_back(nullptr);
        }
        memo[n] = &result;
        return result;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<string> output = s.generateParenthesis(4);
    for (auto s : output) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}