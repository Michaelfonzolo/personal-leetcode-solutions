/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    // This is an O(n^2) solution, but generally performs
    // with about O(n) complexity except for "palindrome-dense"
    // inputs.
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1) {
            return s;
        }

        // Odd palindromes
        int k, max_o = 0, max_oi = 0, max_e = 0, max_ei = 0;
        for (int i = 0; i < n; i++) {
            k = 1;
            while ((i - k >= 0) && (i + k < n) && (s[i - k] == s[i + k])) {
                k++;
            }
            if (k - 1 > max_o) {
                max_o = k - 1;
                max_oi = i;
            }
        }
        
        // Even palindromes
        for (int i = 0; i < n - 1; i++) {
            k = 0;
            while ((i - k >= 0) && (i + k + 1 < n) && (s[i - k] == s[i + k + 1])) {
                k++;
            }
            if (k > max_e) {
                max_e = k;
                max_ei = i;
            }
        }

        if (2 * max_o + 1 > 2 * max_e) {
            return s.substr(max_oi - max_o, 2 * max_o + 1);
        } else {
            return s.substr(max_ei - max_e + 1, 2 * max_e);
        }
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;

    string input;
    while (getline(cin, input) && !input.empty()) {
        cout << sol.longestPalindrome(input) << endl;
    }
}