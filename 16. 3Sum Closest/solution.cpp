// Once you have 3Sum, this one's pretty easy

/*
Given an array nums of n integers and an integer target, find three integers in nums 
such that the sum is closest to target. Return the sum of the three integers. You may 
assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int min_error = INT32_MAX;
        int closest_sum = 0;
        int hi, lo, sum;
        for (int i = 0; i < n; i++) {
            lo = i + 1;
            hi = n - 1;
            while (lo < hi) {
                sum = nums[i] + nums[lo] + nums[hi];
                if (abs(sum - target) < min_error) {
                    closest_sum = sum;
                    min_error = abs(sum - target);
                }

                if (sum < target) {
                    lo++;
                } else if (sum > target) {
                    hi--;
                } else if (sum == target) {
                    return target;
                }
            }
        }
        return closest_sum;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<int> input = {-1, 2, 1, -4};
    cout << s.threeSumClosest(input, 1) << endl;

    return 0;
}