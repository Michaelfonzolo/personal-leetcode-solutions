/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* sum = new ListNode(0);
        ListNode* current = sum;
        int d, carry = 0;
        while (l1 || l2) {
            d = carry;
            d += l1 ? l1->val : 0;
            d += l2 ? l2->val : 0;
            carry = d/10;
            d %= 10;

            current->val = d;

            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
            if ((l1 || l2) || carry) {
                current->next = new ListNode(0);
                current = current->next;
            }
        }

        if (carry)
            current->val = carry;

        return sum;
    }

    void printListNode(ListNode* l) {
        while (l->next != nullptr) {
            cout << l->val << " -> ";
            l = l->next;
        }
        cout << l->val;
    }

    ListNode* constructListNode(int nums[], int size) {
        ListNode* l = new ListNode(0);
        ListNode* crnt = l;
        for (int i = 0; i < size; i++) {
            crnt->val = nums[i];
            if (i < size - 1)
            {
                crnt->next = new ListNode(0);
                crnt = crnt->next;
            }
        }
        return l;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    int n1[] = {2, 4, 3, 3, 9, 1, 4, 7, 9, 9, 8, 5};
    int n2[] = {5, 6, 7, 4, 8, 2, 3, 5, 1, 0, 9, 2, 6, 6};
    sol.printListNode(
        sol.addTwoNumbers(
            sol.constructListNode(n1, 12),
            sol.constructListNode(n2, 14)
        )
    );
    cout << endl;

    system("pause");
    return 0;
}
