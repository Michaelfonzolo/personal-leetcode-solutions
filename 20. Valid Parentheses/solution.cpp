#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> history;
        for (char c : s) {
            switch (c) {
                case '(':
                case '{':
                case '[':
                    history.push(c);
                    break;
                case ')':
                    if (history.empty() || history.top() != '(') {
                        return false;
                    }
                    history.pop();
                    break;
                case '}':
                    if (history.empty() || history.top() != '{') {
                        return false;
                    }
                    history.pop();
                    break;
                case ']':
                    if (history.empty() || history.top() != '[') {
                        return false;
                    }
                    history.pop();
                    break;
            }
        }
        return history.empty();
    }
};

int main(int argc, char const *argv[]) {
    Solution s;

    cout << boolalpha;
    cout << s.isValid("([])()(()({}))") << endl;
    cout << s.isValid("[][[{({{})}}]]") << endl;

    return 0;
}