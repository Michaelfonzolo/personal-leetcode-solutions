/*
Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2

Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1

Clarification:

What should we return when needle is an empty string? This is a great question to 
ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. 
This is consistent to C's strstr() and Java's indexOf().
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    // Naive algorithm
    int strStr(string haystack, string needle) {
        int n = haystack.size(), k = needle.size();

        if (n == 0 && k == 0) {
            return 0;
        }

        bool is_needle = true;
        for (int i = 0; i < n - k + 1; i++) {
            is_needle = true;
            for (int j = 0; j < k; j++) {
                if (haystack[i + j] != needle[j]) {
                    is_needle = false;
                    break;
                }
            }
            if (is_needle) {
                return i;
            }
        }
        return -1;
    }

    // Knuth-Morris-Pratt Algorithm
    int strStr_KMP(string haystack, string needle) {
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    cout << s.strStr("hello", "ll") << endl;
    cout << s.strStr("aaaaaa", "bba") << endl;
    cout << s.strStr("", "abc") << endl;
    cout << s.strStr("abc", "") << endl;
    cout << s.strStr("", "") << endl;
    cout << s.strStr("a", "a") << endl;
    cout << s.strStr("abc", "abc") << endl;

    return 0;
}