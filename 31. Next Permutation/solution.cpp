/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // Algorithm Thoughts
        // ==================
        //
        // First Try:
        // ----------
        // When we swap two elements in a permutation, a_i and a_j, with i < j, then the resulting 
        // permutation will have greater lexicographic order if a_i < a_j. We need to find the pair
        // a_i < a_j, i < j, that minimizes the resulting permutation amongst all possible swaps.
        //
        // Suppose we have a_i < a_j, and a_k < a_l. What criteria guarantees the swap (a_i, a_j)
        // will be less than the swap (a_k, a_l)?
        //
        // Clearly, if i < k, then the swap (a_k, a_l) is less, so the swap furthest to the end
        // is among the lexicographically lowest swaps. If we have swaps (a_k, a_j) and (a_k, a_l),
        // then clearly the lower swap is the swap (a_k, min(a_j, a_l)).
        //
        // Hence, the best swap will be the furthest to the end with the lowest second term.
        //
        // Example: (2, 4, 3, 6, 1, 5)
        // Possible Swaps: (2, 4), (2, 3), (2, 6), (2, 5), (4, 6), (4, 5), (3, 6), (3, 5), (1, 5)
        // Best Swap: (1, 5)
        // Next: (2, 4, 3, 6, 5, 1)
        //
        // ===============
        //
        // Finding the optimal swap in linear time.
        //
        // Clearly, we need to start from the end. We just need to find the first point
        // at which the list is decreasing (starting from the end), and then go forward
        // from that point to find the smallest possible swap.
        //
        // Second Try
        // ----------
        // The first try doesn't work because it's predicated in the notion that the next permutation
        // will always be a swap away from the current permutation. This is not true. Consider (1, 3, 2).
        // The above algorithm would find the swap (1, 2) and return (2, 3, 1), which is not the next
        // permutation. The next permutation is (2, 1, 3).
        //
        // The work above, however, isn't entirely useless. The first swap to get to the next permutation will
        // indeed be the one furthest to the end of the list, we just need to determine what to do next
        // after the swap.
        //
        // The above algorithm will find the largest i such that a_i < a_{i + 1} >= a_{i + 2} >= ... >= a_n.
        // Then, it will find j such that a_i < a_j, and a_i >= a_{j+1}, which is the smallest possible swap.
        // Now, if we swap a_i and a_j, we get the following list:
        //
        // a_j, a_{i + 1} >= a_{i + 2} >= ... >= a_{j - 1} > a_i >= a_{j + 1} ... >= a_n
        //
        // where we know a_{j - 1} > a_i since a_{j - 1} >= a_j in the original list, and a_j > a_i by
        // assumption. Since this list starting at a_{i + 1} is decreasing, the lexicographically next
        // permutation will be
        //
        // a_j, a_n <= a_{n - 1} <= ... <= a_{j + 1} <= a_i < a_{j - 1} <= ... <= a_{i + 1}

        int n = nums.size(), i = n - 1; // i is the index of the for loop
        int si, sj; // The indices of the swap
        for (; i >= 0; i--) {
            if (i < n - 1 && nums[i] < nums[i + 1]) {
                // We've found the furthest possible swap starting point
                si = i;

                // Now search for the lowest possible swap end point
                sj = i + 1;
                int min = INT32_MAX, min_sj = sj;
                while (sj < n) {
                    if (nums[si] < nums[sj] && nums[sj] <= min) {
                        min = nums[sj];
                        min_sj = sj;
                    }
                    sj++;
                }
                sj = min_sj;
                break;
            }    
        }
        if (i < 0) {
            // If the list is increasing starting from the end, then it's the final permutation.
            // Reversing it will put it in ascending order, which is the first permutation.
            reverse(nums.begin(), nums.end());
        } else {
            // Swap si and sj
            int temp = nums[si];
            nums[si] = nums[sj];
            nums[sj] = temp;
            // Reverse si to the end.
            reverse(nums.begin() + si + 1, nums.end());
        }
    }
};

string vecToStr(vector<int> vec) {
    stringstream ss;
    for (int i : vec) {
        ss << i << " ";
    }
    return ss.str();
}

int main(int argc, char const *argv[]) {
    Solution s;

    vector<int> input = {2, 3, 1, 3, 3};
    s.nextPermutation(input);
    cout << vecToStr(input) << endl;

    return 0;
}