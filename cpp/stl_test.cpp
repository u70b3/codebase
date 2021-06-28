#include <cmath>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> vi{3, -1, 2, -100, -20, -20, -20};

// min_element一样
void test_max_element()
{
    auto res1 = max_element(vi.begin(), vi.end());
    auto pos1 = distance(vi.begin(), res1);
    assert(pos1 == 0);

    auto res2 = max_element(vi.begin(), vi.end(), [](int lhs, int rhs)
                            { return (abs(lhs) < abs(rhs)); });
    auto pos2 = distance(vi.begin(), res2);
    assert(pos2 == 3);
}

void test_for_each()
{
    for_each(vi.begin(), vi.end(), [](int i) {});
}

void test_find()
{
    auto res1 = find(vi.begin(), vi.end(), -20);
    auto pos1 = distance(vi.begin(), res1);
    assert(pos1 == 4);

    auto res2 = find_if(vi.begin(), vi.end(), [](int i)
                        { return i < -50; });
    auto pos2 = distance(vi.begin(), res2);
    assert(pos2 == 3);
}
void test_count()
{
    auto res1 = count(vi.begin(), vi.end(), -20);
    // -20 出现 3 次
    assert(res1 == 3);

    auto res2 = count_if(vi.begin(), vi.end(), [](int i)
                         { return i < 0; });
    // 小于 0 的有 5 个
    assert(res2 == 5);
}
void test_copy()
{
    // copy
    // copy_n
    // copy_if
}
void test_all()
{
    test_max_element();
    test_for_each();
    test_find();
    test_count();
    test_copy();
}

int main()
{
    test_all();
    cout << "all test cases passed!" << endl;
};