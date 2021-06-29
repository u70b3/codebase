#include <cmath>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream> // std::stringstream

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
void test_remove()
{
    std::string str1 = "kid;and;u70b3;and;lbs";
    str1.erase(std::remove(str1.begin(), str1.end(), ';'),
               str1.end());
    assert(str1 == string("kidandu70b3andlbs"));

    std::string str2 = "kid\n and\u70b3 \t  and\n\nlbs";
    str2.erase(std::remove_if(str2.begin(),
                              str2.end(),
                              [](unsigned char x)
                              { return std::isspace(x); }),
               str2.end());
    assert(str1 == string("kidandu70b3andlbs"));
}
void test_copy()
{
    // copy
    // copy_n
    // copy_if
}

void test_split()
{
    string line = "kid and u70b3 and lbs";

    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(line);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    // Printing the token vector
    // for (int i = 0; i < tokens.size(); i++)
    //     cout << tokens[i] << '\n';
    assert(tokens[2] == string("u70b3"));
}

void test_all()
{
    test_max_element();
    test_for_each();
    test_find();
    test_count();
    test_remove();
    test_copy();
    test_split();
}

int main()
{
    test_all();
    cout << "all test cases passed!" << endl;
};

// g++ stl_test.cpp -std=c++17 -o test && ./test && rm ./test
