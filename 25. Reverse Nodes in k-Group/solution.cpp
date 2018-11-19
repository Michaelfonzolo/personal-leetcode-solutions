/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number
 of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Note:

Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) {
            return head;
        }

        int counter = 0;
        ListNode* crnt = head;
        while (crnt) { crnt = crnt->next; counter++; }

        if (counter < k) {
            return head;
        }

        crnt = head->next;
        ListNode* temp = crnt;
        ListNode* prev = head;
        for (int i = 0; i < k - 1; i++) {
            temp = temp->next;
            crnt->next = prev;

            prev = crnt;
            crnt = temp;
        }
        head->next = reverseKGroup(temp, k);
        return prev;
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

    ListNode* result = s.reverseKGroup(head, 4);
    cout << "done" << endl;
    while (result != NULL) {
        cout << result->val << endl;
        result = result->next;
    }

    return 0;
}
