
// This solution SUCKS. If I want to get better at DP, I have to start thinking in terms of
// subproblems. A better solution (though not mine) can be found in solution2.cpp.



/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) {
            return s.empty();
        }
        else if (p == ".*") {
            return true;
        }

        // This problem is actually harder than it looks, and it has to do with the ".*" pattern.
        // For example, suppose I'm given the pattern "a.*bcb.*d". What are some strings that it matches?
        //
        // "abcbd" is a match, grouped as: (a)[](bcb)[](d)
        // "abcbde" is _not_ a match because it must end with d
        // "abcbdebcbd" _is_ a match, grouped as: (a)[bcbde](bcb)[](d)
        // "abcbdebcbded" is a match, grouped as: (a)[bcbde](bcb)[de](d)
        // "abcbdebcbded" is _also_ a match when grouped as (a)[](bcb)[dedbcbde](d)
        //
        // In essense, this tells us that there are multiple ways of matching subgroups of the given
        // string to subpatterns of the given pattern, in such a way that _some groupings may match_
        // whereas _other groups may fail_. For example, if the _only_ way we grouped "abcbdebcbd"
        // was as (a)[](bcb)[](d), then this wouldn't be a match because we would have left over
        // characters. Similarly, if we grouped "abcbdebcbded" as (a)[bcbde](bcb)[](d), we also
        // wouldn't have a match.
        //
        // Possible Solution (Recursion)
        // =============================
        // Each time we encounter a ".*" in the pattern (with a character after the "*", since a string ending
        // with ".*" is easy to check), then we iterate through every possible grouping of characters, and check
        // if the substring starting after each matches the subpattern after the ".*". If any of these are true,
        // then we're done.
        // 
        // Question: Is P.*.*Q equivalent to P.*Q for any patterns P, Q?
        //    I think so...
        //
        // Question: What is the worst case complexity of the recursive solution?
        //    What about patterns like .*a.*a.*a? How does this perform on "aaaaaa"?
        //    
        //    At the first '.*a' we have 6 possible groups: [], [a], [aa], [aaa], [aaaa], [aaaaa].
        //    the second '.*a' has 5, 4, 3, 2, 1, and 0 groups respectively for each group generated
        //    by the first '.*a'. This makes 5 + 4 + 3 + 2 + 1 = 15 groups. This kind of growth continues
        //    essentially exponentially.
        //
        //    For .*a.*a.*a, one can show that aa...a (with n a's) has (n - 1 choose 2) valid groupings.
        //    For .*a.*a.*a.*a, this is (n - 1 choose 3).
        //    For .*a.*a... .*a (with k '.*a's), this is (n - 1 choose k - 1).
        //
        //    This is clearly atrocious performance, but right now it's all I've got :/

        int pn = p.size(), sn = s.size();

        // First, reduce C*C*C*... to just C* (including C == .)

        int k;
        string new_p = "";
        for (int i = 0; i < pn; i++) {
            new_p += p[i];
            if (p[i] == '*') {
                k = 0;
                while ( (i + k + 2 < pn) &&             // If we can keep going...
                        (p[i - 1] == p[i + k + 1]) &&   // ...and the next block has the same first character...
                        (p[i + k + 2] == '*') ) {       // ...and the next block ends with '*'...
                    k += 2; //  ...then proceed to the next block
                }
                // Otherwise move ahead to the next i
                i += k;
            }
        }
        cout << new_p << endl;
        p = new_p;

        // Assuming our string has no repeated ".*" entries, start parsing.
        char cp, cp2;
        int pi, si;
        pair<int, int> top;
        vector<pair<int, int>> queue = {make_pair(0, 0)};
        while (!queue.empty()) {
            top = queue.back();
            queue.pop_back();
            pi = top.first, si = top.second;

            // If we're done the pattern but not the string, then the current grouping
            // isn't a match.
            //
            // Note: it is possible for pi < pn && si == sn for a match grouping. For
            // example, abc* matches ab, but once we get to the c*, pi < pn but si == sn.
            if (pi == pn) {
                if (si == sn) {
                    return true;
                }
                continue;
            }

            cp = p[pi];
            if (('a' <= cp && cp <= 'z') || cp == '.') {
                if (pi + 1 < pn && p[pi + 1] == '*') {
                    // Pattern is C* for some C (potentially C = .)
                    if (pi + 2 == pn) {
                        if (cp == '.') {
                            return true;
                        }
                        while (si < sn && s[si] == cp) { si++; }
                        if (si == sn) {
                            return true;
                        }
                        continue;
                    }

                    cp2 = p[pi + 2];
                    int i = 0;
                    while (si + i < sn) {
                        if (i == 0 && (cp2 == '.' || s[si] == cp2)) {
                            queue.push_back(make_pair(pi + 2, si));
                        }
                        else if (i > 0) {
                            if (cp != '.' && s[si + i - 1] != cp) {
                                break;
                            }

                            if (cp2 == '.' || s[si + i] == cp2) {
                                queue.push_back(make_pair(pi + 2, si + i));
                            }
                        }
                        i++;
                    }
                }
                else {
                    if (si == sn || (cp != '.' && s[si] != cp)) {
                        continue;
                    }
                    queue.push_back(make_pair(pi + 1, si + 1));
                }
            }
        }
        return false;
    }

    void check(string s, string p, bool expected) {
        bool received = isMatch(s, p);
        if (expected != received) {
            cout << "[WRONG] ";
        }
        cout << "isMatch(" << s << ", " << p << ") => " << received;
        cout << ", Expected: " << expected << endl;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;

    cout << boolalpha;

    /*
    sol.check("abc", "abc", true);
    sol.check("aa", "a", false);
    sol.check("aa", "a*", true);
    sol.check("aaa", "a*a", true);
    sol.check("aab", "c*a*b", true);
    sol.check("aba", ".ba", true);
    sol.check("abba", ".ba", false);
    sol.check("abba", ".*ba", true);
    sol.check("mississippi", "mis*is*p*.", false);
    sol.check("aaa", ".*a.*a.*a", true);
    sol.check("aa", ".*a.*a.*a", false);
    sol.check("abcbd", "a.*bcb.*d", true); 
    sol.check("abcbdebcbd", "a.*bcb.*d", true);
    sol.check("abcbdebcbded", "a.*bcb.*d", true); 
    sol.check("abcdef", "abc.*", true);
    sol.check("cccac", "c*.*", true);
    */

    string input, input_string, input_pattern;
    stringstream ss;
    while (getline(cin, input) && !input.empty()) {
        ss = stringstream(input);
        ss >> input_string;
        ss >> input_pattern;
        cout << sol.isMatch(input_string, input_pattern) << endl;
    }
    
    return 0;
}