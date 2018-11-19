/*
Given a linked list, swap every two adjacent nodes and return its head.

Example:

Given 1->2->3->4, you should return the list as 2->1->4->3.
Note:

Your algorithm should use only constant extra space.
You may not modify the values in the list's nodes, only nodes itself may be changed.
*/

#include <cstddef>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* root = head->next;
        ListNode* crnt_2 = root;
        ListNode* crnt_1 = head;
        ListNode* temp = NULL;
        ListNode* prev = NULL;
        while (crnt_1 && crnt_2) {
            // This is the swapping procedure
            temp = crnt_2->next;
            crnt_2->next = crnt_1;
            if (prev) {
                prev->next = crnt_2;
            }
            crnt_1->next = temp;

            // This is the setup for the next swap
            prev = crnt_1;
            crnt_1 = temp;
            if (crnt_1 != NULL) {
                crnt_2 = crnt_1->next;
            } else {
                crnt_2 = NULL;
            }
        }
        return root;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    ListNode* head = new ListNode(1);
    ListNode* x2 = new ListNode(2);
    ListNode* x3 = new ListNode(3);
    ListNode* x4 = new ListNode(4);
    ListNode* x5 = new ListNode(5);
    ListNode* x6 = new ListNode(6);

    head->next = x2;
    x2->next = x3;
    x3->next = x4;
    x4->next = x5;
    x5->next = x6;

    ListNode* result = s.swapPairs(head);
    while (result != NULL) {
        cout << result->val << endl;
        result = result->next;
    }
    return 0;
}
