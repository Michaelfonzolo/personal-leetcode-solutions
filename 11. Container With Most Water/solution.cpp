/*
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two 
lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

(image)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area 
of water (blue section) the container can contain is 49.

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Naive Solution
    int maxArea_naive(vector<int>& height) {
        int n = height.size();
        int max_area = 0, current_area;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                current_area = (j - i) * min(height[i], height[j]);
                if (current_area > max_area) {
                    max_area = current_area;
                }
            }
        }
        return max_area;
    }

    int maxArea_smarter(vector<int>& height) {
        // Why does this solution work?
        // 
        // Start with l = 0, r = n - 1. Suppose h[l] < h[r]. Then this is the largest container
        // that can be formed with h[l], since for all k > l, either h[k] < h[r] in which case
        // the container is smaller, or h[k] >= h[r] in which case the container is the same size
        // as if h[k] == h[r], so there is no need to consider h[l] anymore.
        //
        // Essentially, at each step (l, r), if h[l] < h[r] then A(h[l], h[k]) <= A(h[l], h[r]) for
        // all k, and so moving r will not result in an increase in the area of the container, hence
        // we have to move l. Since l(i) > l(i - 1) and we've already checked l(i - 1), the only option
        // is to increase l(i). A similar argument holds for h[l] >= h[r].
        //
        // Increasing l when h[l] < h[r] or decreasing r when h[l] >= h[r] doesn't _guarantee_ an 
        // increase in area, however doing the opposite _guarantees no change or a decrease_ in
        // the container area.
        //
        // 
        int n = height.size();
        int start = 0, end = n - 1;
        int max_area = 0, current_area;
        while (start < end) {
            current_area = (end - start) * min(height[start], height[end]);
            cout << "(" << start << ", " << end << ") => " << current_area << endl;
            if (current_area > max_area) {
                max_area = current_area;
            }
            if (height[start] < height[end]) {
                start++;
            }
            else {
                end--;
            }
        }
        return max_area;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    vector<int> input = {500,10,10,5000,501};
    cout << s.maxArea_smarter(input) << " " << s.maxArea_naive(input) << endl;

    return 0;
}