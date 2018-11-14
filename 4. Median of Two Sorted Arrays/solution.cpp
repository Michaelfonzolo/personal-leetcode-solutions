/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {        
        // Given A and B ordered lists of numbers, how can we define the median of A ∪ B?
        // Well, for any ordered list C of numbers, if we split C into two parts (C[:j], C[j:]),
        // (or (C[:j], C[j+1:]) if |C| is odd), then the median is (max(C[:j])+min(C[j:]))/2 if
        // |C[:j]| = |C[j:]|. A similar case holds for C[:j] and C[j+1:]
        //
        // This is all good for a given single list C, but how can we do this same operation on A ∪ B
        // without concatenating and sorting the new list, which is O(N ln N) where N = |A| + |B|?
        //
        // Well, we can choose two integers i, j and split both A and B into two groups simultaneously:
        //
        // A[:i] ∪ B[:j], A[i:] ∪ B[j:]
        //
        // In order for the split to be "right down the middle", we need |A[:i] ∪ B[:j]| = |A[i:] ∪ B[j:]|
        // 
        // NOTE: We should mention that although we're using the "∪" symbol, this is more of an implicit
        // "concatenation", since duplicate values in A and B _affect_ the median.
        //
        // The condition |A[:i] ∪ B[:j]| = |A[i:] ∪ B[j:]| can be expressed as
        //
        // i + j = (|A| - i) + (|B| - j)
        //
        // or, writing j in terms of i, we have
        //
        // j = (|A| + |B|)/2 - i
        //
        // NOTE: These formulas change slightly if |A| + |B| is odd.
        //
        // NOTE: Neither i nor j can violate the constraints 1 <= i <= |A|, 1 <= j <= |B|. For 
        // j = (|A| + |B|)/2 - i, we can rearrange 1 <= j <= |B| to get (|A|-|B|)/2 <= i <= (|A|+|B|)/2 - 1,
        // and so
        //
        //  max(1, (|A| - |B|)/2) <= i <= min(|A|, (|A| + |B|)/2 - 1)
        //
        // For j = (|A| + |B| + 1)/2 - i, we get
        //
        //  max(1, (|A| - |B| + 1)/2) <= i <= min(|A|, (|A| + |B| - 1)/2)
        //
        // Now, we have a relationship that tells us when |A[:i] ∪ B[:j]| = |A[i:] ∪ B[j:]|, but we need
        // to impose another condition on our sets in order for them to be a proper "median split".
        // More specifically, in order for median = (max(A[:i] ∪ B[:j]) + min(A[i:] ∪ B[j:]))/2, we need
        // max(A[:i] ∪ B[:j]) <= min(A[i:] ∪ B[j:]), and so since max(A[:i]) <= min(A[i:]) and likewise for
        // B and j, it follows that we need the following "cross-inequalities" to hold:
        //
        // max(B[:j]) <= min(A[i:])     &&      max(A[:i]) <= min(B[j:])
        //
        // or, since A and B are ordered:
        //
        // B[j-1] <= A[i]       &&      A[i-1] <= B[j]
        //
        // Now we have enough information in order to find the appropriate "median split". All we need to do
        // is iterate through all possible values of i, set j = (|A| + |B|)/2 - i, and find the value of i
        // such that B[j - 1] <= A[i] and A[i - 1] <= B[j]. Once we have this, then the median can be
        // calculated as
        //
        // median = (max(A[i - 1], B[j - 1]) + min(A[i], B[j])) / 2
        //
        // We can actually perform this iteration using a binary search to get logarithmic complexity over
        // simply linear. Namely, lets think about what happens if we have a given value of i, which
        // _doesn't_ satisfy the above "cross-inequalities".
        //
        // If A[i - 1] > B[j], then decreasing i (which simultaneously increases j) will cause A[i - 1] to
        // decrease and B[j] to increase. We will eventually arrive at a point where A[i - 1] <= B[j].
        //
        // If B[j - 1] > A[i], then increasing i (which decreases j) will cause A[i] to increase and
        // B[j - 1] to decrease. We will eventually arrive at a point where B[j - 1] <= A[i].
        //
        // There are some edge cases to check. If A[i] < B[j] for all choices (i, j) (not just those
        // related by the formula for j in terms of i), then B[j - 1] <= A[i] is never satisfied. Similarly
        // if A[i] > B[j] for all (i, j), then A[i - 1] <= B[j] is never satisfied. These edge cases
        // can be solved easily however.
        //
        // The other important edge cases occur in two places:
        //  1. i = |A|
        //  2. j = |B|
        //
        //  1. If i = |A|, then A[i] doesn't make sense, so we can't check if B[j - 1] <= A[i].
        //     However, even if i = |A|, the split will be (A ∪ B[:j], B[j:]). We know that
        //     |B[j:]| - |A ∪ B[:j]| ∈ {0, 1}, and since only elements of B are in the upper
        //     half of the split, we only really need to check that A[i - 1] <= B[j]. Hence,
        //     the check B[j - 1] <= A[i] is superfluous, and there is no way that B[j - 1] > A[i]
        //     could occur (i.e., we would never have to increase i after i = |A|; either this is
        //     the correct split, or we need to decrease i).
        //  2. If j = |B|, we can handle this in a similar way to the case i = |A|.
        //
        // Question: Is it possible for i = 0 or j = 0?
        // Answer: Well, i = (imin + imax) / 2 at every stage, and imin >= 1, so the only possible
        //  way for i = 0 is for imin = 1, and imax = 0.
        //  If |A| + |B| is even, the imin = 1 => (|A| - |B|) / 2 <= 1, or |A| <= 2 + |B|, which is
        //  totally possible. If imax = 0, then (|A| + |B|)/2 - 1 = 0, so |A| + |B| = 2, which is
        //  only possible if |A| = |B| = 1 (assuming we've caught the trivial cases |A| = 0 and
        //  |B| = 0).
        //  If |A| + |B| is odd, then imin = 1 => |A| <= 1 + |B|, which is also possible. If imax = 0,
        //  then (|A| + |B| - 1) / 2 = 0, which implies |A| + |B| = 1, which is impossible assuming
        //  |A|, |B| > 0.
        //  Hence, there is only one case where i = 0: |A| = |B| = 1. We can just catch this as an
        //  edge case.
        //
        //  What about j = 0? For |A| + |B| even, j = 0 corresponds to i = (|A| + |B|)/2, but we
        //  specifically chose i <= (|A| + |B|)/2 - 1 < (|A| + |B|)/2, so this is impossible. For
        //  |A| + |B| odd, j = 0 <=> i = (|A| + |B| + 1)/2, but again i <= (|A| + |B| - 1)/2, so
        //  this is also impossible.
        //
        //  In conclusion, the only time i = 0 or j = 0 is if |A| = |B| = 1, in which case i = 0.
        //
        // Qusetion: Is it possible for i = |A| and j = |B| simultaneously?
        // Answer: For |A| + |B| even, if i = |A|, and j = |B|, then (|A| + |B|)/2 - |A| = |B|,
        //  so (|B| - |A|)/2 = |B|, which itself implies (after some simple mainpulation) that
        //  |A| + |B| = 0, which is impossible.
        //  For |A| + |B| odd, if i = |A| and j = |B| then (|A| + |B| + 1)/2 - |A| = |B|, or
        //  (after simplification) |A|+ |B| = 1, which is also impossible assuming we've already
        //  processed |A| = 0 or |B| = 0.
        //
        //  In conclusion, it is not possible for i = |A| and j = |B| simultaneously, so we don't
        //  have to worry about this case.
        //
        // Hence, by restricted the new search domain of i to either [x >= i] or [x <= i] at each step,
        // we can perform a binary search of the appropriate value i for the split.
        
        int m = nums1.size(), n = nums2.size();
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }
        bool even = (n + m) % 2 == 0;
        int m1 = even ? (n + m) / 2 - 1 : (n + m - 1) / 2;
        int m2 = even ? (n + m) / 2     : (n + m - 1) / 2;
        int m_left, m_right;

        // This catches some edge cases that the binary search algorithm below doesn't
        // handle well.
        if (m == 0) {
            return (nums2.at(m1) + nums2.at(m2)) / 2.0;
        }
        else if (nums1.at(m - 1) < nums2.at(0)) {
            m_left  = m1 <= m - 1 ? nums1.at(m1) : nums2.at(m1 - m);
            m_right = m2 <= m - 1 ? nums1.at(m2) : nums2.at(m2 - m);
            return (m_left + m_right) / 2.0;
        }
        else if (nums2.at(n - 1) < nums1.at(0)) {
            m_left  = m1 <= n - 1 ? nums2.at(m1) : nums1.at(m1 - n);
            m_right = m2 <= n - 1 ? nums2.at(m2) : nums1.at(m2 - n);
            return (m_left + m_right) / 2.0;
        }

        int H = (m + n + (int)(!even)) / 2;
        int imin = 0;
        int imax = fmin(m, H);
        // We set imax <= H because if i > H then j < 0, which doesn't make sense.
        // Similarly, i > m doesn't make sense either.
        int i, j;

        do {
            i = (imin + imax) / 2;
            j = H - i;

            // Question: how do we guarantee imin <= imax?
            // Question: if imin == imax, is the do-while condition guaranteed to be False?
            // 
            // Assume imin < imax. Then imin <= i <= imax. If i = imin, we need case 2 to be true,
            // so that we don't set imax = imin - 1. Similarly, if i = imax, we need case 1 to be
            // true so that we don't set imin = imax + 1.
            //
            // Otherwise, if imin < i < imax, then either case produces imin', imax' such that
            // imin' <= imax', and so by induction we'll eventually arrive at imin == imax.
            //
            // If i = imin, there are 3 cases, either i is the correct split index, we need to
            // increase i, or we need to decrease i. If we decrease i, then we're violating the
            // assumption made at each step in the search that the desired i is in [imin, imax],
            // and so this should never occur. A similar argument follows for i = imax.
            //
            // Hence, imin < imax => imin' <= imax'.
            //
            // As for the second question, if imin == imax, must the loop terminate? Assume 
            // imin == imax and B[j - 1] > A[i] or A[i - 1] > B[j]. The first condition says
            // we have to increase i, and the second condition says we have to decrease i, both
            // of which violate the contract that i' in [imin, imax], which is assumed true at
            // each step in the loop. 

            // All of these questions are based on the fundamental assertion that we have a
            // "loop contract" which must be satisfied at each step in the loop. Namely, we need
            // the ideal i' to be in [imin, imax] at all steps in the loop. If we assume this is
            // true for _given_ imin, imax at the start of the loop, and show that the new
            // [imin', imax'] created at the end of the loop _also_ satisfies this contract, then
            // we're done.

            if (i > 0 && j < n && nums1.at(i - 1) > nums2.at(j)) {
                // We have to _decrease_ the search space, and since the correct i 
                // isn't equal to the current i, we can restrict the search space 
                // to [imin, i - 1] rather than simply [imin, i]. 
                
                // This also helps to prevent an infinite loop bug that occurs when
                // i = imax.
                imax = i - 1;
            }

            else if (j > 0 && i < m && nums2.at(j - 1) > nums1.at(i)) {
                // Similar reasoning above; we only need to search [i + 1, imax],
                // not [i, imax].
                imin = i + 1;
            }

        } while (! (
            ((i == m || j == 0) && nums1.at(i - 1) <= nums2.at(j)) ||
            ((i == 0 || j == n) && nums2.at(j - 1) <= nums1.at(i)) ||
            (nums2.at(j - 1) <= nums1.at(i) && nums1.at(i - 1) <= nums2.at(j))
        ));
        // If i == |A| and A[i - 1] <= B[j], then the split (A ∪ B[:j], B[j:]) is
        // the right split (since both sides have equal cardinality and everything
        // on the left is less than everything on the right).
        //
        // Similarly, if j == 0 and A[i - 1] <= B[j], then the split (A[:i], A[i:] ∪ B)
        // is the right split (for the same reason).
        //
        // If i == 0 or j == |B|, as in the above cases, and B[j-1] <= A[i], then the splits
        // (B[:j], A ∪ B[j:]) or (A[:i] ∪ B, A[i:]) are respectively correct.
        //
        // Finally, if 0 < i < |A| and 0 < j < |B|, and B[j - 1] <= A[i] and A[i - 1] <= B[j],
        // then (A[:i] ∪ B[:j], A[i:] ∪ B[j:]) is the correct split.

        if (i == 0) {
            m_right = nums2.at(j - 1);
        }
        else if (j == 0) {
            m_right = nums1.at(i - 1);
        }
        else {
            m_right = fmax(nums1.at(i - 1), nums2.at(j - 1));
        }

        if (!even) {
            return m_right;
        }

        if (i == m) {
            m_left = nums2.at(j);
        }
        else if (j == n) {
            m_left = nums1.at(i);
        }
        else {
            m_left = fmin(nums1.at(i), nums2.at(j));
        }

        return (m_right + m_left) / 2.0;
    }
};

int main(int argc, char const *argv[]) {
    Solution sol;
    vector<int> A = {1};
    vector<int> B = {4};
    cout << sol.findMedianSortedArrays(A, B) << endl;
    system("pause");
}