// We solve the general k-sum problem and call it for k = 4. k-sum can be solved in O(n^(k - 1)).

/*
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    // This method assumes nums is sorted.
    // min_i is the min index iterating through nums
    set<vector<int>> kSum_recursive(vector<int>& nums, int target, int k, int min_i) {
        int n = nums.size(), sum, lo, hi;
        set<vector<int>> result;
        if (k == 2) {
            lo = min_i, hi = n - 1;
            while (lo < hi) {
                sum = nums[lo] + nums[hi];
                if (sum < target) {
                    lo++;
                }
                else if (sum > target) {
                    hi--;
                }
                else {
                    result.insert({nums[lo], nums[hi]});
                    lo++;
                    hi--;
                }
            }   
        }
        else {
            set<vector<int>> subresult;
            for (int i = min_i; i < n - 1; i++) {
                subresult = kSum_recursive(nums, target - nums[i], k - 1, i + 1);
                for (vector<int> terms : subresult) {
                    terms.push_back(nums[i]);
                    result.insert(terms);
                }
            }
        }
        return result;
    }

    vector<vector<int>> kSum(vector<int>& nums, int target, int k) {
        sort(nums.begin(), nums.end());
        set<vector<int>> result = kSum_recursive(nums, target, k, 0);
        vector<vector<int>> v_res;
        v_res.reserve(result.size());
        for (vector<int> terms : result) {
            v_res.push_back(terms);
        }
        return v_res;
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        return kSum(nums, target, 4);    
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<int> input = {1, 0, -1, 0, -2, 2};
    vector<vector<int>> output = s.fourSum(input, 0);
    for (auto terms : output) {
        for (auto i : terms) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}