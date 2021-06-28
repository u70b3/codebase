#include <cmath>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> vi{3, -1, 2, 100, -20};

void test_max_element()
{
    auto res1 = max_element(vi.begin(), vi.end());
    auto pos1 = distance(vi.begin(), res1);
    cout << pos1 << endl;

    auto res2 = max_element(vi.begin(), vi.end(), [](int lhs, int rhs)
                            { return (abs(lhs) < abs(rhs)); });
    auto pos2 = distance(vi.begin(), res2);
    cout << pos2 << endl;
}

void test_all()
{
    test_max_element();
}

int main()
{
    test_all();
};