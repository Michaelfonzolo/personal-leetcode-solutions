/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int crnt_max = 0, crnt_size = 0, s_size = s.size();
        set<char> seen;
        for (string::size_type i = 0; i + crnt_max < s_size; i++) {
            if (i > 0) {
                seen.erase(s[i-1]);
            }
            
            while (seen.count(s[i+crnt_size]) < 1 && i+crnt_size < s_size) {
                seen.insert(s[i+crnt_size]);
                crnt_size++;
            }
            if (crnt_size > crnt_max){
                crnt_max = crnt_size;
            }
            // If the prev_size is n, then the crnt_size is _at least_ n - 1.
            crnt_size--;
        }
        return crnt_max;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    /*
    stringstream ss;
    for (int i = 0; i < 100000; i++) {
        ss << (char)(97 + (rand() % 10));
    }
    string s = ss.str();
    */
    string s = "abca";
    cout << sol.lengthOfLongestSubstring(s) << endl;
    system("pause");
}