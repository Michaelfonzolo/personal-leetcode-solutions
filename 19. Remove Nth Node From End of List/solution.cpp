/*
Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // Obvious solution
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int N = 0;
        ListNode* crnt = head;
        while (crnt != nullptr) { crnt = crnt->next; N++; }

        if (n > N) {
            return head;
        } else if (n == N) {
            return head->next;
        }
        int i = 0;
        crnt = head;
        while (i < N - n - 1) {
            crnt = crnt->next;
            i++;
        }
        crnt->next = crnt->next->next;
        return head;
    }

    // One-pass solution
    ListNode* removeNthFromEnd_onePass(ListNode* head, int n) {
        ListNode * first = head, * second = head;
        for (int i = 0; i < n; i++) {
            if (!first) {
                return head;
            }
            first = first->next;
        }
        if (first == nullptr) {
            return head->next;
        }
        while (first->next) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return head;
    }

    ListNode* vectorToListNode(vector<int> values) {
        ListNode * root = nullptr;
        ListNode * node = nullptr;
        ListNode * prev = nullptr;

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
        if (head != nullptr) {
            while (head->next) {
                ss << head->val << " -> ";
                head = head->next;
            }
            ss << head->val;
        }
        return ss.str();
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    ListNode* input = s.vectorToListNode({1, 2, 3, 4, 5});
    cout << s.listNodeToString(s.removeNthFromEnd_onePass(input, 1)) << endl;

    return 0;
}