/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
Note:

All given inputs are in lowercase letters a-z.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strings) {
        string prefix = "";
        int n = strings.size();

        if (n == 0) {
            return prefix;
        }
        int min_len = max_element(strings.begin(), strings.end(),
                                  [](const string &a, const string &b) {
                                      return a.size() < b.size();
                                  })->size();
        if (min_len == 0) {
            return prefix;
        }

        char crnt_char;
        bool shared;

        for (int i = 0; i < min_len; i++) {
            shared = true;
            crnt_char = strings[0][i];
            
            for (int j = 0; j < n; j++) {
                shared &= strings[j][i] == crnt_char;
                if (!shared) break;
            }
            if (shared) {
                prefix += crnt_char;
            } else {
                break;
            }
        }

        return prefix;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<string> input = {"flower", "flow", "flight"};
    cout << s.longestCommonPrefix(input) << endl;

    return 0;
}