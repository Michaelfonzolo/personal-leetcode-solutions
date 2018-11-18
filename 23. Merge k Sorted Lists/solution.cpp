/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // The priority queue solution is O(log(k) N) where k is the number of lists and
    // N is the sum of the lengths of the k lists.
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Dumb edge cases
        if (lists.empty() || all_of(lists.begin(), lists.end(), [](ListNode* n){return n == NULL;})) {
            return NULL;
        }

        auto cmp = [](pair<int, int> left, pair<int, int> right) { return left.first > right.first; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> next_values(cmp);
        unordered_map<int, ListNode*> heads;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] == NULL) {
                continue;
            }
            heads.insert({i, lists[i]});
            next_values.push(make_pair(heads[i]->val, i));
        }
        
        ListNode* root = NULL;
        ListNode* node = NULL;
        ListNode* prev = NULL;
        pair<int, int> top;
        int crnt_index;
        while (!heads.empty()) {
            top = next_values.top();
            next_values.pop();
            crnt_index = top.second;

            if (heads.count(crnt_index) > 0) {
                heads[crnt_index] = heads[crnt_index]->next;
                if (!heads[crnt_index]) {
                    heads.erase(crnt_index);
                } else {
                    next_values.push(
                        make_pair(heads[crnt_index]->val, crnt_index));
                }
            }

            if (!node) {
                node = new ListNode(top.first);
                if (prev) {
                    prev->next = node;
                }
                if (!root) {
                    root = node;
                }
            }
            prev = node;
            node = node->next;
        }
        return root;
    }

    ListNode* vectorToListNode(vector<int> values) {
        ListNode * root = NULL;
        ListNode * node = NULL;
        ListNode * prev = NULL;

        for (auto it = values.begin(); it != values.end(); it++) {
            if (!node) {
                node = new ListNode(*it);
                if (!root) {
                    root = node;
                }
                if (prev) {
                    prev->next = node;
                }
            }
            prev = node;
            node = node->next;
        }
        return root;
    }

    string listNodeToString(ListNode* head) {
        stringstream ss;
        if (head != NULL) {
            while (head->next) {
                ss << head->val << " -> ";
                head = head->next;
            }
            ss << head->val;
        }
        return ss.str();
    }
};

int main(int argc, const char *argv[]) {
    Solution s;

    vector<ListNode*> input;
    /*
    input.push_back(s.vectorToListNode({1, 4, 5}));
    input.push_back(s.vectorToListNode({1, 3, 4}));
    input.push_back(s.vectorToListNode({2, 6}));
    */
    input.push_back(s.vectorToListNode({}));
    input.push_back(s.vectorToListNode({1, 4, 5, 8}));
    cout << s.listNodeToString(s.mergeKLists(input)) << endl;

    return 0;
}