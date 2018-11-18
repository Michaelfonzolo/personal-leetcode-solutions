/*
Merge two sorted linked lists and return it as a new list. The new list should be made by 
splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
*/

#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* root = nullptr;
        ListNode* node = nullptr;
        ListNode* prev = nullptr;
        int val = 0;
        while (l1 || l2) {
            if (l1 && l2) {
                val = min(l1->val, l2->val);
                if (val == l1->val) {
                    l1 = l1->next;
                } else {
                    l2 = l2->next;
                }
            } else if (l1) {
                val = l1->val;
                l1 = l1->next;
            } else if (l2) {
                val = l2->val;
                l2 = l2->next;
            }
            if (!node) {
                node = new ListNode(val);
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
};

int main(int argc, char const *argv[])
{
    Solution s;
    return 0;
}
