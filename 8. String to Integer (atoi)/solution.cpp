/*
Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until 
the first non-whitespace character is found. Then, starting from this character, 
takes an optional initial plus or minus sign followed by as many numerical digits 
as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral 
number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral 
number, or if no such sequence exists because either str is empty or it contains 
only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within 
the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out 
of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

Example 1:

Input: "42"
Output: 42

Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        bool negative = false, encountered_numeric = false;
        int n = str.size();

        // First, ignore whitespace
        int i = 0, x = 0, d = 0;
        while (isspace(str[i])) i++;

        // Check if the input is negative
        if (str[i] == '-') {
            negative = true;
            i++;
        }
        else if (str[i] == '+') {
            i++;
        }

        while (i < n) {
            // Check if the next character is a digit
            if (48 <= str[i] && str[i] <= 57) {
                encountered_numeric = true;
                d = str[i] - 48;

                // Check if the next digit will cause overflow.
                // x >= (INT32_MAX - d) / 10 <=> 10 * x + d >= INT32_MAX
                if (!negative && x >= (INT32_MAX - d) / 10.0) {
                    return INT32_MAX;
                }
                // Of course, we have to be careful about INT32_MIN
                // -x <= (INT32_MIN + d) / 10 <=> 10 * (-x) - d <= INT32_MIN
                else if (negative && -x <= (INT32_MIN + d) / 10.0) {
                    return INT32_MIN;
                } else {
                    x = 10 * x + d;
                }
            }
            else {
                if (encountered_numeric) {
                    break; // Extra characters encountered after numeric characters
                }
                return 0; // No valid conversion performed: no numeric characters encountered
            }
            i++;
        }
    
        return negative ? -x : x;    
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
    cout << "'1000' => "          << sol.myAtoi("1000")          << endl;
    cout << "'42' => "            << sol.myAtoi("42")            << endl;
    cout << "'        -42' => "   << sol.myAtoi("        -42")   << endl;
    cout << "'   3391 words' => " << sol.myAtoi("   3391 words") << endl;
    cout << "'214748364' => "     << sol.myAtoi("214748364")     << endl;
    cout << "'2147483647' => "    << sol.myAtoi("2147483647")    << endl;
    cout << "'2147483648' => "    << sol.myAtoi("2147483648")    << endl;
    cout << "'-2147483648' => "   << sol.myAtoi("-2147483648")   << endl;
    cout << "'-2147483647' => "   << sol.myAtoi("-2147483647")   << endl;
    cout << "'-9113427894' => "   << sol.myAtoi("-9113427894")   << endl;
    cout << "'words and 4' => "   << sol.myAtoi("words and 4")   << endl;

    system("pause");
}