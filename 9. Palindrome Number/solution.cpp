/*
Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?
*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        int nd = 0;
        int digits[40]; // Far more digits than we need
        while (x > 0) {
            digits[nd] = x % 10;
            x /= 10;
            nd++;
        }
        for (int i = 1; i <= nd / 2; i++) {
            if (digits[i - 1] != digits[nd - i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
    cout << sol.isPalindrome(1221) << endl;
    cout << sol.isPalindrome(199424991) << endl;
    cout << sol.isPalindrome(19339) << endl;
    system("pause");
}