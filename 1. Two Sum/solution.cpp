/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// This is the first piece of C++ code that I'm proud of :D

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> indices;
        
        int num;
        unordered_map<int, int> seen; // O(1) lookup of seen terms
        unordered_map<int, int>::const_iterator got;
        for (unsigned int i = 0; i < nums.size(); i++)
        {
            num = nums[i];
            got = seen.find(target - num);
            if (got == seen.end())
            {
                seen.insert({num, i});
                continue;
            }
            else
            {
                // If we're here, then got->first + num = target, so
                // (got->second, i) is the pair of indices to return.
                indices.push_back(got->second);
                indices.push_back(i);
                break;
            }
        }
        return indices;
    }
};

int main(int argc, char const *argv[])
{
    cout << "Hello!" << endl;;

    string input;
    int num_count, next_num, target;
    vector<int> nums, indices;
    Solution sol;

    while (getline(cin, input) && !input.empty())
    {   
        istringstream iss(input);
        iss >> num_count;
        nums.clear();

        for (int i = 0; i < num_count; i++)
        {
            iss >> next_num;
            nums.push_back(next_num);
        }

        iss >> target;

        indices = sol.twoSum(nums, target);
        cout << indices[0] << " " << indices[1] << endl;
    }

    return 0;
}
