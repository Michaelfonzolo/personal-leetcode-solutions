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
#include <sstream>
#include <string>
#include <vector>

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
        // The KMP algorithm is based off the idea of a "suffix table" T, which tells us
        // for any given _mismatch_ of the needle within the haystack, how far we have to
        // jump forward in order to find the next possible match. 
        //
        // It's based off the idea that if we determine that needle doesn't match haystack[i:], 
        // then we don't  necessarily have to start the next search at haystack[i+1:], we may 
        // be able to jump further ahead.
        //
        // This is the "idea" of the algorithm, but how does it work in practice? Suppose we have
        // haystack[i + j] == needle[j], for j up to some k (haystack[i + k] != needle[k]). Assuming
        // we haven't found a match, where do we have to jump next? Well, if the next possible match
        // occurs at haystack[i + j], then it must be that needle[j:k] == needle[:k-j].
        //
        // This means, we can preprocess a table T of length = len(haystack) that tells us, for each
        // k, what the smallest j is such that needle[j:k] == needle[:k-j], (or equivalently, what the
        // largest possible proper prefix of needle[:k] is which is also a proper suffix of needle[:k]).
        //
        // Now, once we've determined that the next possible match occurs at haystack[i + j], we
        // don't need to check haystack[i + j + j'] = needle[j'] for all j', since we know that
        // haystack[i + j:k] == needle[:k - j], and so we can start checking for matches at j' = k.
        //
        // Hence, assuming we've built T, we can find matches in O(len(haystack)) time. Building T
        // with the trivial algorithm would take O(len(needle)^2) time, but it can actually be done
        // in O(len(needle)) time.
        //
        // Building the Table
        // ==================
        // Here we use W = needle.
        //
        // T[i] = length of the longest possible proper prefix of W which is also a substring
        //        (proper suffix?) of W[:i+1].
        // Example: W = "ABCDABD"
        // T[0] = 0, since there are no proper substrings of "A"
        // T[1] = 0, since the only proper substring of "AB" is "B", which is not a prefix of W.
        // T[2] = 0, since "ABC" has "BC" and "C" as proper suffixes but neither are prefixes of W.
        // T[3] = 0 for the same reason
        // T[4] = 1, because "ABCDA" has "A" as a proper suffix, and "A" is a proper prefix of W
        // T[5] = 2, because "ABCDAB" has "AB" as a proper suffix, and "AB" is a proper prefix of W
        // T[6] = 0, because "ABCDABD" has no proper suffix which is a proper prefix of W
        //
        // How can we build T in linear time? Well, it turns out we only have to check a 
        // small subset of all possible suffixes, based on information about the _previous_
        // largest suffix found.
        //
        // Consider W = "ACAC". T[0] = 0, T[1] = 0, and T[2] = 1. Now, we observe that T[3] = 2,
        // since "AC" is a suffix of "ACAC" and a prefix of "ACAC". But do we have to check both
        // "C" and "AC"? No, we only need to start checking at "AC". This is because we already
        // know that T[3 - 1] = 1, which tells us the largest suffix of "ACA" which is a prefix
        // of "ACA" is "A". If we add the next character to that suffix ("C"), then we already 
        // know that the first character is a prefix of "ACAC", and so we only have to check the
        // new characters.
        //
        // In general, if T[i - 1] = m, then we we can start checking T[i] at the length m+1
        // suffix. If, however, no suffix after the length m suffix is also a prefix, then
        // no suffix of _any_ length is also a prefix, and so T[i] = 0.

        int k = needle.size(), n = haystack.size();
        if (n == 0) {
            if (k == 0) {
                return 0;
            }
            return -1;
        } else if (k == 0) {
            return 0;
        }

        vector<int> T = KMP_wordTable(needle);
        int i = 0, j = 0;
        while (i <= n - k) {
            while (haystack[i + j] == needle[j] && j < k) {
                j++;
            }
            if (j == k) {
                return i;
            } else if (j > 0) {
                j = T[j - 1];
            }
            i++;
        }
        return -1;
    }

    vector<int> KMP_wordTable(string needle) {
        vector<int> T(needle.size());
        T[0] = 0; // This is always the case as there are no proper suffixes of a W[:1], a string with 1 character.

        // Lets see how this works in more detail, since it's actually slightly nontrivial
        // (and kinda DP). First, we prove some facts.
        //
        // Fact: T[i+1] <= T[i] + 1
        //
        // This can be proven with induction. Suppose a[1]...a[T[i - 1]] == a[i - T[i - 1]]...a[i - 1]
        // where a is our pattern. Now we ask, is it possible for T[i] > T[i - 1] + 1? If this were
        // true, then we would have
        //
        //      a[1]...a[T[i - 1] + 1]a[T[i - 1] + 2] == a[i - T[i - 1] - 1]...a[i]
        //
        // (We can choose to end at a[T[i - 1] + k], for any k > 1, but this gets the gist of the argument
        // across).
        //
        // However, if the above string equality holds, then
        // 
        //      a[1]...a[T[i - 1] + 1] == a[i - T[i - 1] - 1]...a[i - 1]
        //
        // but this would imply that T[i - 1] is _not_ the largest possible k for which
        // a[1]...a[k] == a[i - k]...a[i - 1], contradicting the definition of T[i - 1]. Hence,
        // we must have that T[i] <= T[i - 1] + 1.
        //
        // If T[i] == T[i - 1] + 1, all we have to do is check that a[T[i - 1] + 1] == a[i], and
        // continue. On the other hand, if T[i] < T[i - 1], how do we find this new T[i]? Well
        // we know that a[1]...a[T[i - 1]] == a[i - T[i - 1]]...a[i - 1], how can we find j
        // such that a[1]...a[j] == a[i - j + 1]...a[i]?
        //
        // I don't know :/ I can't figure it out
        // https://cs.stackexchange.com/questions/100335/confused-about-constructing-the-failure-table-in-knuth-morris-pratt-algorithm

        int j;
        for (int i = 1; i < needle.size(); i++) {
            j = T[i - 1];
            // Find largest j s.t. T[:j+1] == T[i-j:i+1]
            while (j > 0 && needle[j] != needle[i]) {
                j = T[j - 1];
            }
            T[i] = (needle[j] == needle[i]) ? j + 1 : j;
        }
        return T;
    }
};

string vecToStr(vector<int> v) {
    stringstream ss;
    for (int i : v) {
        ss << i << " ";
    }
    return ss.str();
}

int main(int argc, char const *argv[]) {
    Solution s;

    cout << s.strStr_KMP("hello", "ll") << endl;
    cout << s.strStr_KMP("aaaaaa", "bba") << endl;
    cout << s.strStr_KMP("", "abc") << endl;
    cout << s.strStr_KMP("abc", "") << endl;
    cout << s.strStr_KMP("", "") << endl;
    cout << s.strStr_KMP("a", "a") << endl;
    cout << s.strStr_KMP("abc", "abc") << endl;
    cout << s.strStr_KMP("aaabaaaabaaaab", "aaaab") << endl;
    cout << s.strStr_KMP("aaaaaaaaa", "aaaaaaaa") << endl;
    cout << s.strStr_KMP("aaaaaaaaa", "aaaaaaaaa") << endl;
    cout << s.strStr_KMP("babba", "bbb") << endl;
    cout << vecToStr(s.KMP_wordTable("bbb")) << endl;
    cout << vecToStr(s.KMP_wordTable("xaxxyxaxxx")) << endl;

    return 0;
}