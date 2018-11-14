/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within 
the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, 
assume that your function returns 0 when the reversed integer overflows.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int32_t reverse(int32_t x) {
        if (x < 0) {
            // There's just that one little annoying case where if x == INT32_MIN,
            // then -x overflows. Fortunately, if x == INT32_MIN then we know that
            // reversing x will just result in underflow anyways, which we treat as
            // 0 (as per the description above).
            return x == INT32_MIN ? 0 : -reverse(-x);
        }
        unsigned long reversed = 0;
        while (x != 0) {
            reversed = 10 * reversed + (x % 10);
            x /= 10;
        }
        if (reversed > INT32_MAX) {
            return 0;
        }
        return reversed;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;

    
    cout << sol.reverse(321) << endl;
    cout << sol.reverse(9212) << endl;
    cout << sol.reverse(150) << endl;
    cout << sol.reverse(0) << endl;
    cout << sol.reverse(-19900009) << endl;
    cout << sol.reverse(1000000) << endl;
    cout << sol.reverse(-2147483648) << endl;

    system("pause");
}