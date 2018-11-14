#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    string number_as_string = "77";
    int number = stoi(number_as_string);

    cout << number << endl;
    system("pause");
}
