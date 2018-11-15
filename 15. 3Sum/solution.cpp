// Note: This question is really dumb and annoying. They don't specify enough about the output
// to come up with a reasonable algorithm without messing around a bit. Even the given example
// doesn't demonstrate if, for example, duplicate indices are allowed (which apparently they're
// not, it's just that the example shows solutions which aren't in the same order as the original
// list.) Also _sometimes_ you can't reuse values but _other_ times you can, like they want the
// expected output of [0, 0, 0, 0] to be [[0, 0, 0]].

// This question is really dumb.

/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    // O(n^2) (kinda) solution
    // Doesn't quite work, it returns duplicates
    vector<vector<int>> threeSum_nsquared_duplicates(vector<int>& nums) {
        unordered_map<int, vector<pair<int, int>>> a_plus_b;
        int n = nums.size(), a, b;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                a = nums[i], b = nums[j];
                if (a_plus_b.count(a + b) > 0) {
                    a_plus_b[a + b].push_back(make_pair(i, j));
                }
                else {
                    a_plus_b[a + b] = {make_pair(i, j)};
                }
            }
        }

        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            if (a_plus_b.count(-nums[i]) > 0) {
                for (auto indices : a_plus_b[-nums[i]]) {
                    if (indices.second <= i) {
                        result.push_back({nums[indices.first], 
                                         nums[indices.second],     
                                         nums[i]});
                    }
                }
            }
        }


        return result;
    }

    // O(n^2) solution (without duplicates)
    vector<vector<int>> threeSum_nsquared(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        set<vector<int>> result;
        int lo, hi, sum, n = nums.size();
        for (int i = 0; i < n; i++) {
            lo = i + 1;
            hi = n - 1;
            while (lo < hi) {
                sum = nums[lo] + nums[i] + nums[hi];
                if (sum > 0) {
                    hi--;
                } else if (sum < 0) {
                    lo++;
                }
                else {
                    result.insert({nums[lo], nums[i], nums[hi]});
                    lo++;
                    hi--;
                }
            }
        }
        vector<vector<int>> v_res(result.begin(), result.end());
        return v_res;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<int> input = {3, 0, -2, -1, 1, 2};
    // -2 -1 0 1 2 3
    auto output = s.threeSum_nsquared(input);
    for (auto terms : output) {
        for (auto i : terms) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}