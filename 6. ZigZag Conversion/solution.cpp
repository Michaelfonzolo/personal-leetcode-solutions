/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

/*
Lets do some basic pattern matching. Suppose our string S = s1 s2 ... sn, and the number
of rows is r. Then we can write S in "zigzag" format as

s1            s(2r-1)               s(4r-3)
s2    s(2r-2) s(2r)         s(4r-4) s(4r-2)
|    /        |            /        |              /    ...
|  s(r+1)     |      s(3r-1)        |       s(5r-3)
sr            s(3r-2)               s(5r-4)

and so our string S in zigzag format is

s1 s(2r-1) s(4r-3) s(6r-5) ... s(2ir-(2i-1)) ...
s2 s(2r-2) s(2r)   s(4r-4) s(4r-2) s(6r-6) s(6r-4) ... s(2ir-2i)     s(2ir-(2i-2)) ...
s3 s(2r-3) s(2r+1) s(4r-5) s(4r-1) s(6r-7) s(6r-3) ... s(2ir-(2i+1)) s(2ir-(2i-3)) ...
s4 s(2r-4) s(2r+2) s(4r-6) s(4r)   s(6r-8) s(6r-2) ... s(2ir-(2i+2)) s(2ir-(2i-4)) ...
.
.
.
sk s(2r-k) s(2r+(k-2)) s(4r-(k+2)) s(4r+(k-4)) s(6r-(k+4)) s(6r+(k-6)) ... s(2ir-(2i+k-2)) s(2ir-(2i-k)) ...
.
.
.
sr s(3r-2) s(5r-4) ... s((2i+1)r-2i) ...

So our approach will be pretty simple: nested for loop, iterating first through k, then through i,
then just adding s(2ir-(2i+k-2)) s(2ir-(2i-k)) each time, checking that none of the indices exceed n.
*/

// NOTE: This solution is practically unreadable, but it works.

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int r = numRows, n = s.size();
        if (r == 1 || r >= n) {
            // The algorithm below depends on 1 < r <= n. If r = 1, then
            // 2*i*r - (2*i - 1) = 1 is constant in i, meaning the first
            // while loop never terminates.
            return s;
        }
            
        string ss(n, 'a');

        int i = 0, j = 0, i2;
        while (2*i*r - (2*i - 1) <= n) {
            ss[j++] = s[2*i*r - (2*i - 1) - 1];
            i++;
        }

        for (int k = 2; k < fmin(n, r); k++) {
            ss[j++] = s[k - 1];
            i = 1;
            while (2*i*r - (2*i + k - 2) <= n) {
                ss[j++] = s[2*i*r - (2*i + k - 2) - 1];
                i2 = 2*i*r - (2*i - k);
                if (i2 <= n) {
                    ss[j++] = s[i2 - 1];
                }
                i++;
            }
        }

        i = 0;
        while ((2*i + 1)*r - 2*i <= n) {
            ss[j++] = s[(2*i + 1)*r - 2*i - 1];
            i++;
        }
        return ss;
    }

    // SUPER OPTIMIZED VERSION
    /*
    string convert(string s, int numRows) {
        int r = numRows, n = s.size();
        if (r == 1 || r >= n) {
            return s;
        }
        string ss(n, 'a');

        int c = 2*(r - 1), j = 0;
        
        int i1 = 1;
        while (i1 <= n) {
            ss[j++] = s[i1 - 1];
            i1 += c;
        }

        int i2, i2n;
        for (int k = 2; k < r; k++) {
            ss[j++] = s[k - 1];
            
            i2 = c - k + 2;
            while (i2 <= n) {
                ss[j++] = s[i2 - 1];
                i2n = i2 + 2*(k - 1);
                if (i2n <= n) {
                    ss[j++] = s[i2n - 1];
                }
                i2 += c;
            }
        }

        int i4 = r;
        while (i4 <= n) {
            ss[j++] = s[i4 - 1];
            i4 += c;
        }
        return ss;
    }
    */
};

int main(int argc, char const *argv[]) {
    Solution sol;
    string s = "AB";
    int numRows;
    cin >> numRows;
    cout << sol.convert(s, numRows) << endl;

    system("pause");
    return 0;
}